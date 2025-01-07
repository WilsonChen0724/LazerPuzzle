#include "Info.h"

// Define image paths
const char pptPaths[27][15] = {
    "source/1.png", 
    "source/2.png",
    "source/3.png",
    "source/4.png",
    "source/5.png",
    "source/6.png",
    "source/7.png",
    "source/8.png",
    "source/9.png",
    "source/10.png",
    "source/11.png",
    "source/12.png",
    "source/13.png",
    "source/14.png",
    "source/15.png",
    "source/16.png",
    "source/17.png",
    "source/18.png",
    "source/19.png",
    "source/20.png",
    "source/21.png",
    "source/22.png",
    "source/23.png",
    "source/24.png",
    "source/25.png",
    "source/26.png",
    "source/27.png",
};


Info::Info(SDL_Renderer* renderer, const std::string& bgImagePath, int bnum, Button* buttons, int* assignButtons, int assignLength,
                           TTF_Font* font, SDL_Color textColor)
    : scene(renderer, bgImagePath, 3, buttons, assignButtons, assignLength),currentPage(0), font(font), textColor(textColor) 
{
    
    navigationButtons = new ButtonPair(renderer, "source/left_button.png", "source/left_button.png", "source/right_button.png", "source/right_button.png", {320, 20, 80, 80}, {880, 20, 80, 80}, 0, 1, 0, 26, font, textColor);
	graph = new LTexture;
}

Info::~Info() {
    //delete graph
	delete graph;
}


void Info::InfoRender(SDL_Renderer* renderer) {
    // Fade in the background
    if (!hasFadedIn) {
        SDL_Rect dstRect = {0, 0, 1280, 720}; // Full screen or modify as needed
        fadeInPicture(renderer, background.getTexture(), &dstRect, 50); // Fade in over 50 steps
        hasFadedIn = true; // Mark as faded in
    } else {
        // Render background without fade-in
        background.renderOrigin(0, 0, renderer);
    }

    // Render buttons
    for (int i = 0; i < buttonNumber; i++) {
        buttons[i].render(renderer);
    }
	
    // Render the current graph
    if (currentPage >= 0 && currentPage < 27) {
    	graph->loadFromFile(renderer, pptPaths[currentPage]);
        graph->render(150, 100, 1000, 550, renderer); // Example position for the graph
    }

    navigationButtons->PairRender(renderer);
}

void Info::handleEvent(SDL_Event& e, int mouseX, int mouseY) {
    // check hover
    navigationButtons->checkButtonPairHover(mouseX, mouseY);
    
	if (navigationButtons->handleClick(e)) {
    	int nextValue = navigationButtons->getValue();
    	if (nextValue >= 0 and nextValue <= 27) {
    		currentPage = nextValue;
		} 
        printf("Current page: %d\n", currentPage);
    }
}

