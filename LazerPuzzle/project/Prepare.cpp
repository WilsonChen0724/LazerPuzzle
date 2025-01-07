#include "Prepare.h"

Prepare::Prepare(SDL_Renderer* renderer, const std::string& bgImagePath, int bnum, Button* buttons, int* assignButtons, int assignLength, TTF_Font* font, SDL_Color textColor)
    : scene(renderer, bgImagePath, bnum, buttons, assignButtons, assignLength), font(font), textColor(textColor) {
    // Initialize the ButtonPairs
    
    buttonPairs.emplace_back(renderer, "source/left_button.png", "source/left_button.png",         		 
                                "source/right_button.png", "source/right_button.png",
                                SDL_Rect{400, 50, 80, 80}, SDL_Rect{600, 50, 80, 80}, 180, 30, 60, 240, font, textColor);	// game countdown time 
    																											//(180 30 120 240) -> (init, interval, lowbnd, upbnd)
	titles.emplace_back("Game Countdown Time");
	 
    buttonPairs.emplace_back(renderer, "source/left_button.png", "source/left_button.png",
                                "source/right_button.png", "source/right_button.png",
                                SDL_Rect{400, 150, 80, 80}, SDL_Rect{600, 150, 80, 80}, 3, 1, 2, 6, font, textColor);			// lazer period time
    titles.emplace_back("Lazer Period Time");
    
    buttonPairs.emplace_back(renderer, "source/left_button.png", "source/left_button.png",
                                "source/right_button.png", "source/right_button.png",
                                SDL_Rect{400, 250, 80, 80}, SDL_Rect{600, 250, 80, 80}, 0, 1, 0, 1, font, textColor);			// whether to enable items mode
    titles.emplace_back("Enable Items Mode");
    
    buttonPairs.emplace_back(renderer, "source/left_button.png", "source/left_button.png",
                                "source/right_button.png", "source/right_button.png",
                                SDL_Rect{400, 350, 80, 80}, SDL_Rect{600, 350, 80, 80}, 0, 1, 0, 5, font, textColor);			// which map to play
    titles.emplace_back("Select Map");
    
    buttonPairs.emplace_back(renderer, "source/left_button.png", "source/left_button.png",          //Player 1 skills 
                                "source/right_button.png", "source/right_button.png",
                                SDL_Rect{400, 450, 80, 80}, SDL_Rect{600, 450, 80, 80}, 0, 1, 0, 6, font, textColor);
    titles.emplace_back("Player 1 Skills");
    
    buttonPairs.emplace_back(renderer, "source/left_button.png", "source/left_button.png",          //Player 2 skills 
                                "source/right_button.png", "source/right_button.png",
                                SDL_Rect{400, 550, 80, 80}, SDL_Rect{600, 550, 80, 80}, 0, 1, 0, 6, font, textColor);
    titles.emplace_back("Player 2 Skills");
    
    
	const std::string mapPaths[6] = {
        "source/map_0.png",
        "source/map_1.png",
        "source/map_2.png",
        "source/map_3.png",
        "source/map_4.png",
		"source/map_5.png"
    };
	std::string tmpSkillTexts[7] = {
        "none",
        "dash",
        "invisible",
        "kill",
        "teleport",
		"swap",
		"pull" 
    };
    // Push each item from the array into the vector
    for (int i = 0; i < 7; ++i) {
        skillTexts.push_back(tmpSkillTexts[i]);
    }
    
    currentMapIndex = 0;
    mapLength = 6;
    
    lazerPeriodTime = 3;
    itemsEnable = 0;
    player1Skill = 0;
	totalTime = 180;
    player2Skill = 0;
    
    for (int i = 0; i < 6; ++i) {
        if (!maps[i].loadFromFile(renderer, mapPaths[i])) {
            printf("Failed to load map: %s\n", mapPaths[i].c_str());
        }
    }
    
	titleBackground.loadFromFile(renderer, "source/title_background.png");
}

Prepare::~Prepare() {
    // Vector will automatically clean up
}

void Prepare::checkPairHover(int mouseX, int mouseY) {
    for (ButtonPair& buttonPair : buttonPairs) {
        buttonPair.checkButtonPairHover(mouseX, mouseY);
    }
}

void Prepare::PrepareRender(SDL_Renderer* renderer) {
    // Fade in the background
    if (!hasFadedIn) {
        SDL_Rect dstRect = {0, 0, 1280, 720}; // Full screen or modify as needed
        fadeInPicture(renderer, background.getTexture(), &dstRect, 50); // Fade in over 50 steps
        hasFadedIn = true; // Mark as faded in
    } else {
        // Render background without fade-in
        background.renderOrigin(0, 0, renderer);
    }

    // Render all ButtonPairs
    for (ButtonPair& buttonPair : buttonPairs) {
        buttonPair.PairRender(renderer);

    }
    
    // Render maps
    if (currentMapIndex < mapLength) {
    	maps[currentMapIndex].renderOrigin(800, 100, renderer);
	}
    
    
    // Render all ButtonPairs and their titles
    for (size_t i = 0; i < buttonPairs.size(); ++i) {
        buttonPairs[i].PairRender(renderer);

        // Render the title above each ButtonPair
        SDL_Color titileColor = {250, 248, 230, 0};
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, titles[i].c_str(), titileColor);
        if (textSurface != nullptr) {
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_Rect textRect = {
                buttonPairs[i].getLeftButtonX()-300, // Align title with left button
                buttonPairs[i].getLeftButtonY()+20, // Render above the ButtonPair
                textSurface->w,
                textSurface->h
            };
            SDL_Rect bgRect = {textRect.x - 5, textRect.y - 5, textSurface->w + 10, textSurface->h + 10};
            titleBackground.render(textRect.x - 5, textRect.y - 5, textSurface->w + 10, textSurface->h + 10,renderer);
    		
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);
        }
        if (i == 4 or i == 5) {
	    	// Render the skilltexts
	        SDL_Surface* textSurface = TTF_RenderText_Solid(font, skillTexts[buttonPairs[i].getValue()].c_str(), titileColor);
	        if (textSurface != nullptr) {
	            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	            SDL_Rect textRect = {
	                buttonPairs[i].getRightButtonX()+100, // Align title with left button
	                buttonPairs[i].getRightButtonY()+20, // Render above the ButtonPair
	                textSurface->w,
	                textSurface->h
	            };
	            SDL_Rect bgRect = {textRect.x - 5, textRect.y - 5, textSurface->w + 10, textSurface->h + 10};
	            titleBackground.render(textRect.x - 5, textRect.y - 5, textSurface->w + 10, textSurface->h + 10,renderer);
	    		
	            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	            SDL_FreeSurface(textSurface);
	            SDL_DestroyTexture(textTexture);
	        }    	
		}
    }

    // Render buttons
    for (int i = 0; i < buttonNumber; i++) {
        buttons[i].render(renderer);
    }
}

void Prepare::handleAdjust(SDL_Event& e, Game* gameScene) {
    for (size_t i = 0; i < buttonPairs.size(); ++i) {
        if (buttonPairs[i].handleClick(e)) {
            printf("ButtonPair %zu clicked. Current value: %d\n", i, buttonPairs[i].getValue());
            int tmpvalue = buttonPairs[i].getValue();
            switch (i) {
            	case 0:
            		gameScene->setAssignedTime(tmpvalue);
            		totalTime = tmpvalue;
            		break;
            	case 1:
            		lazerPeriodTime = tmpvalue;
            		break;
				case 2:
					itemsEnable = tmpvalue;
					break;
				case 3:
					currentMapIndex = tmpvalue;
					break;
				case 4:
					player1Skill = tmpvalue;
					break;
				case 5:
					player2Skill = tmpvalue;
					break;
			}
        }
    }
}

int Prepare::getCMapIndex() {
	return currentMapIndex;
}

int Prepare::getLPT() {
	return lazerPeriodTime;
}

bool Prepare::getItemsEn()  {
	return itemsEnable;
}

int Prepare::getP1Skill() {
	return player1Skill;
}

int Prepare::getP2Skill() {
	return player2Skill;
}

int Prepare::getTotalTime() {
	return totalTime;
}
