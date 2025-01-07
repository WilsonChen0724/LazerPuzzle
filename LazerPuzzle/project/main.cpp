#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "player.h"
#include "map.h"
#include "raser.h"
#include "timer.h"
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stack>
#include "Button.h"
#include "MusicPlayer.h"
#include "scene.h"
#include "Game.h"
#include "Prepare.h"
#include "Info.h"
const int SCREEN_WIDTH = 1280 ;
const int SCREEN_HEIGHT = 720;

using namespace std;


SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

// player1
player1 playerA(0);
player2 playerB(0);

//map
map mainMap(1,4);
raserSystem raserSystem(5000);
RTimer fix;
const int32_t fixtime = 60;
int endGame = 3;



// Scenes
//welcome interface
scene* welcomeScene;
Info* infoScene;
scene* settingScene;
Prepare* prepareScene; // preparescene 
Game* gameScene;
scene* overScene;  

//Main loop flag
bool quit = false;

//Event handler
SDL_Event e;

// egg
bool egg = false;


//different stages represent different interface
enum stages{
	welcome, info, prepare, game, setting, over
};

std::stack<stages> stageStack;
stages stage;

// Create a MusicPlayer instance and music flag
MusicPlayer* musicPlayer;

// Fonts and Color
TTF_Font* font;

// mouse state
int mouseX, mouseY;
//welcome Stage functions
void welcomeEvent(scene* welcomeScene) {
	// get mouse state
    SDL_GetMouseState(&mouseX, &mouseY);
    //check Hover
	welcomeScene->checkHover(mouseX, mouseY);
	switch (welcomeScene->handleClick(e)){
        case 0:  //start
           	fadeOut(gRenderer, 50); // Fade out over 50 steps
        	stageStack.push(stage); // Save current stage
        	stage = prepare;           // Change to the game stage
           	welcomeScene->resetFade();
			break;
        case 1:  //guide
	        fadeOut(gRenderer, 50);
	        stageStack.push(stage);
	        stage = info;
	        welcomeScene->resetFade();
           	break;
        case 2: //setting
	        fadeOut(gRenderer, 50);
	        stageStack.push(stage);
	        stage = setting;
	        welcomeScene->resetFade();
           	break;
        default:
           	break; 		
	}       	
}
//info stage functions
void infoEvent(Info* infoScene) {
	// get mouse state
    SDL_GetMouseState(&mouseX, &mouseY);
    //check Hover
	infoScene->checkHover(mouseX, mouseY);
	switch (infoScene->handleClick(e)){
		case 0: 	//setting
			printf("Setting button clicked!\n");
			fadeOut(gRenderer, 50); // Fade out over 50 steps
			stageStack.push(stage); // Save the current stage
			stage = setting;
			infoScene->resetFade();
			break;
		case 1: //return
			printf("Return button clicked!\n");
	        if (!stageStack.empty()) {
				fadeOut(gRenderer, 50); // Fade out over 50 steps
                stage = stageStack.top(); // Go back to the previous stage
                stageStack.pop();        // Remove the top stage
                infoScene->resetFade();
            }
			break;
		default:
			break; 			
	}
	infoScene->handleEvent(e,mouseX, mouseY) ;     	
}
// prepare stage functions
void prepareEvent(scene* preapareScene) {
	// get mouse state
    SDL_GetMouseState(&mouseX, &mouseY);
    //check Hover
	prepareScene->checkHover(mouseX, mouseY);
	prepareScene->checkPairHover(mouseX, mouseY);
	switch (prepareScene->handleClick(e)){
		case 0: 	//setting
			printf("Setting button clicked!\n");
			fadeOut(gRenderer, 50); // Fade out over 50 steps
			stageStack.push(stage); // Save the current stage
			stage = setting;
			prepareScene->resetFade();
			break;
		case 1: //return
			printf("Return button clicked!\n");
	        if (!stageStack.empty()) {
				fadeOut(gRenderer, 50); // Fade out over 50 steps
                stage = stageStack.top(); // Go back to the previous stage
                stageStack.pop();        // Remove the top stage
                prepareScene->resetFade();
            }
			break;
		case 2:
			printf("Go button clicked!\n");
			fadeOut(gRenderer, 50); // Fade out over 50 steps
//			stageStack.push(stage); // Save the current stage
			/////////////////////////////////////////////////////////////////////////////////////////////////////
			playerA.skillAssign(prepareScene->getP1Skill());
			playerB.skillAssign(prepareScene->getP2Skill());
			mainMap.initialize(prepareScene->getItemsEn() ,prepareScene -> getCMapIndex());
			raserSystem.intervalSet(prepareScene -> getLPT()*1000);
			mainMap.mapSetting(gRenderer);
			if(!mainMap.mapRendering(gRenderer)){
		    	printf( "Failed to load map texture image!\n" );
		        
			}
			playerA.loadStatus(gRenderer);
			playerB.loadStatus(gRenderer);
			
			fix.start();

			
			stage = game;
			prepareScene->resetFade();
			break;			
		default:
			break; 			
	}
	prepareScene->handleAdjust(e, gameScene); // 偵測每個buttonPair是否有被更動到      	
}
//over stage functions
void overEvent(scene* overScene) {
	
	// check endgame ///////TODO
	endGame = 3;
	// get mouse state
	playerA.reset();
	playerB.reset();
	raserSystem.reset();
    SDL_GetMouseState(&mouseX, &mouseY);
    //check Hover
	overScene->checkHover(mouseX, mouseY);
	switch (overScene->handleClick(e)){
		case 0:		//home
			printf("Home button clicked!\n");
			fadeOut(gRenderer, 50); // Fade out over 50 steps
			overScene->resetFade();
			while (!stageStack.empty()) {
				stageStack.pop();
			}
            stage = welcome;
			break;
		case 1:		//again
			printf("Again button clicked!\n");
			fadeOut(gRenderer, 50); // Fade out over 50 steps
			overScene->resetFade();
			
			///initialize the variables
			playerA.skillAssign(prepareScene->getP1Skill());
			playerB.skillAssign(prepareScene->getP2Skill());
			mainMap.initialize(prepareScene->getItemsEn() ,prepareScene -> getCMapIndex());
			raserSystem.intervalSet(prepareScene -> getLPT()*1000);
			mainMap.mapSetting(gRenderer);
			if(!mainMap.mapRendering(gRenderer)){
		    	printf( "Failed to load map texture image!\n" );
		        
			}
			playerA.loadStatus(gRenderer);
			playerB.loadStatus(gRenderer);
			
			fix.start();
			
			while (!stageStack.empty()) {
				stageStack.pop();
			}
			stageStack.push(welcome);
			stageStack.push(prepare);
			stage = game;			
			break;
		case 2:		//prepare
			printf("Prepare button clicked!\n");
			fadeOut(gRenderer, 50); // Fade out over 50 steps
			overScene->resetFade();
			while (!stageStack.empty()) {
				stageStack.pop();
			}
			stageStack.push(welcome);			
			stage = prepare;
			break;
		default:
			break; 			
	}      	
}
//setting stage functions
void settingEvent(scene* infoScene, Volume& volume) {
	// get mouse state
    SDL_GetMouseState(&mouseX, &mouseY);
    //check Hover
	settingScene->checkHover(mouseX, mouseY);
	switch (settingScene->handleClick(e)){
		case 0:		//return
			printf("Return button clicked!\n");
	        if (!stageStack.empty()) {
				fadeOut(gRenderer, 50); // Fade out over 50 steps
                stage = stageStack.top(); // Go back to the previous stage
                stageStack.pop();        // Remove the top stage
                settingScene->resetFade();
            }
			break;
		case 1:		//add
			printf("Add button clicked!\n");
			++(*musicPlayer);
			volume.increaseVolume();
			break;
		case 2:		//subtract
			printf("Subtract button clicked!\n");
			--(*musicPlayer);
			volume.decreaseVolume();
			break;
		case 3:
			printf("Egg button clicked\n");
			if (!egg) egg = true;
			else egg = false;
		default:
			break; 			
	}      	
}
bool loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //mainMap
//   mainMap.mapSetting(gRenderer);
//    if(!mainMap.mapRendering(gRenderer)){
//    	printf( "Failed to load map texture image!\n" );
//        success = false;
//	}
    return success;
}

void close()
{
    //Free loaded images


    //Destroy window    
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
	TTF_CloseFont(font);
	TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


int main(int argc, char*argv[]){
	//While application is running
      // Initialize SDL and audio and sdl_ttf
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    if (TTF_Init() == -1) {
    printf("Failed to initialize SDL_ttf: %s\n", TTF_GetError());
    return -1;
	}

	
    // Create window
    gWindow = SDL_CreateWindow("Lazer Puzzle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Create renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Initialize SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return -1;
    }

    // Load media
    
    
    
    if (!loadMedia())
    {
        printf("Failed to load media!\n");
        
    }
    else
    {	
    	// Initialize stages
		stageStack.push(welcome);
		stage = stageStack.top(); // Current stage
		// Initialize color and fonts
		SDL_Color textColor = {0, 0, 0, 255}; // Black color
		font = TTF_OpenFont("source/OpenSans_Bold.ttf", 24);
		if (!font) {
    		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		}
		// Create buttons
		// Buttons
		Button buttons[] = {Button(gRenderer, "source/button_start_default.png", "source/button_start_hover.png", 350, 525, 153, 66), // start
							Button(gRenderer, "source/button_guide_default.png", "source/button_guide_hover.png", 800, 525, 153, 66), // guide
							Button(gRenderer, "source/settings.png", "source/settings.png", 1208, 0, 72, 72), //settings
							Button(gRenderer, "source/return.png", "source/return.png", 0, 0, 72, 72), //return
							Button(gRenderer, "source/add.png", "source/add.png", 400, 200, 72, 72),       //add
							Button(gRenderer, "source/subtract.png", "source/subtract.png", 500, 200, 72, 72),   // subtract
							Button(gRenderer, "source/button_go_default.png", "source/button_go_hover.png", 1000, 600, 153, 66), //Go!!!
							Button(gRenderer, "source/button_home_default.png", "source/button_home_hover.png", 400, 600, 153, 66),	//home
							Button(gRenderer, "source/button_again_default.png", "source/button_again_hover.png", 700, 600, 153, 66),  //again
							Button(gRenderer, "source/button_prepare_default.png", "source/button_prepare_hover.png", 1000, 600, 153, 66), //prepare
							Button(gRenderer, "source/settings.png", "source/settings.png", 1208, 0, 72, 72)};  //egg~
		// Initialize volumes
		Volume volume(gRenderer, 300, 200, 72, 72); // Position (x, y) and size (w, h) 
		volume.loadIcons("source/volume_1.png", "source/volume_2.png", "source/volume_3.png", "source/volume_4.png");
	
		// Initialize scenes
		//welcomeScene
		int welcomeButtons[3] = {0, 1, 2};
	    std::cout << "yes\n";
		welcomeScene = new scene(gRenderer, "source/lazer_puzzle.png", 3, buttons, welcomeButtons, 3);	
		int infoButtons[2] = {2,3};
		infoScene = new Info(gRenderer, "source/lazer_puzzle.png", 2, buttons, infoButtons, 2,  font, textColor);
		int settingButtons[4] = {3, 4, 5, 10};
		settingScene = new scene(gRenderer, "source/lazer_puzzle.png", 4, buttons, settingButtons, 4);
		int gameButtons[2] = {2, 3};
		gameScene = new Game(gRenderer, "source/lazer_puzzle.png", 2, buttons, gameButtons, 2, font, textColor, (SCREEN_WIDTH - 150) / 2, 0, 150, 75); 
		int prepareButtons[3] = {2, 3, 6};
		prepareScene = new Prepare(gRenderer, "source/lazer_puzzle.png", 3, buttons, prepareButtons, 3,  font, textColor);
		int overButtons[3] = {7, 8, 9};
		overScene = new scene(gRenderer, "source/lazer_puzzle.png", 3, buttons, overButtons, 3);
		// Initialize timer
		bool timeflag = false;
						
		//counter for game smoothier
        int counter =0;
        
        //initialize music player
        musicPlayer = new MusicPlayer;
        if (musicPlayer->loadMusic("source/game_bgm.mp3")) {
       		musicPlayer->playMusic();
		}
		// Main loop
        while (!quit)
        {		
        
        
        
			if(stage == game){

				if (!timeflag) {
					
					gameScene->startTimer();// Start the timer (default 3-minute countdown)
					
					timeflag = true;
				} 
				
				
				int lineN;
				if(timeflag){
					
					//std::cout<<gameScene->getRemainTime()<<"\n";
					//std::cout<<"ppp\n";
					//std::cout<<prepareScene->getTotalTime()/3;
					lineN = 5-gameScene->getRemainTime()/(prepareScene->getTotalTime()/5);
					if(gameScene->getRemainTime()==0){
						raserSystem.overtime();
//						std::cout<<"yes\n";
					}
					 
				}
				
				
				if(!raserSystem){
					lineN = 5;
				}
				raserSystem.numberChange(lineN);
		        raserSystem.raserinit(mainMap);
		        raserSystem.raserShoot(mainMap,gRenderer);
		        playerA.loadStatus(gRenderer);
		        playerB.loadStatus(gRenderer);
			}
        
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
                else {
            		if (stage == welcome) {
            			welcomeEvent(welcomeScene);
					}
					else if (stage == info) {
						infoEvent(infoScene);
					}
					else if (stage == prepare) {
						prepareEvent(prepareScene);
					}
					else if (stage == game) {
						//gameEvent() function  
						SDL_GetMouseState(&mouseX, &mouseY);
    					//check Hover
						gameScene->checkHover(mouseX, mouseY);

							switch (gameScene->handleClick(e)){
							case 1: //return
								printf("Return button clicked!\n");
								stage = stageStack.top();
								stageStack.pop();
								///initialize the variables
								playerA.reset();
								playerB.reset();
								raserSystem.reset();
								playerA.skillAssign(prepareScene->getP1Skill());
								playerB.skillAssign(prepareScene->getP2Skill());
								mainMap.initialize(prepareScene->getItemsEn() ,prepareScene -> getCMapIndex());
								raserSystem.intervalSet(prepareScene -> getLPT()*1000);
								mainMap.mapSetting(gRenderer);
								if(!mainMap.mapRendering(gRenderer)){
									printf( "Failed to load map texture image!\n" );
										        
								}
								playerA.loadStatus(gRenderer);
								playerB.loadStatus(gRenderer);		
								fix.start();
								timeflag = false;								
								break;
							default:
								break; 			
						}

	                	playerA.pollEvents(e,mainMap,raserSystem,gRenderer,playerB);
	                	playerB.pollEvents(e,mainMap,raserSystem,gRenderer,playerA);
	                		playerA.crazyAssign(egg);
	                		playerB.crazyAssign(egg);
							if(egg){
								
								++playerA;
								++playerB;
							}						
					}
					else if (stage == setting) {
						//settingEvent() function;
						settingEvent(settingScene, volume); //Notice: volume過去需要加reference 
					}
					else if (stage == over) {
						timeflag = false;
						overEvent(overScene);
					}
					else {
						cout << "Stage error!\n";
					}
				}
			}
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );
			
//            //Render background texture to screen
//            gBackgroundTexture.renderOrigin( 240, 80 ,gRenderer); 先註解掉 
			if (stage == welcome) {
				//welcomeUpdate()
				welcomeScene->sceneRender(gRenderer);
			}
			else if (stage == info) {
				//infoUpdate()
				infoScene->InfoRender(gRenderer);
			}
			else if (stage == prepare) {
				prepareScene->PrepareRender(gRenderer);
			}
			else if (stage == game) {
				//gameUpdate()
				
            	gameScene->GameRender(gRenderer); // gameScene
            	
            	mainMap.mapBackRendering(gRenderer);
				playerA.render(gRenderer);
				playerB.render(gRenderer);	
				mainMap.mapShowing(gRenderer);
				if(fix.counter(fixtime)){
	            	fix.stop();
	            	playerA.move(mainMap);
	            	playerB.move(mainMap);
	            	fix.start();
				}

	            playerA.blockPos();
	            playerB.blockPos();
	            playerA.itemReturn(mainMap);
	            playerB.itemReturn(mainMap);
	            playerA.itemGet(mainMap,gRenderer);
	            playerB.itemGet(mainMap,gRenderer);
	            raserSystem.chainCheck(mainMap, gRenderer);
	            playerA.aliveDetect(mainMap, gRenderer);
	            playerB.aliveDetect(mainMap, gRenderer);
	            playerA.skilldetect(mainMap, gRenderer,playerB);
	            playerB.skilldetect(mainMap, gRenderer,playerA);
	            playerA.itemShow( gameScene);
	            playerB.itemShow( gameScene);
	            if(!playerA.isAlive()&&!playerB.isAlive()){
//	            	std::cout<<"tie";
					endGame = 0;
					overScene->changeBackground(gRenderer, "source/tie.png");
					stage = over;
				}else if(!playerA.isAlive()){
//					std::cout<<"B win";
					endGame = 1;
					overScene->changeBackground(gRenderer, "source/player2win.png");
					stage = over;
				}else if(!playerB.isAlive()){
//					std::cout<<"A win";
					endGame = 2;
					overScene->changeBackground(gRenderer, "source/player1win.png");
					stage = over;
				}else{
					endGame = 3;
				}
				mainMap.mapBackRendering(gRenderer);
			    playerA.render(gRenderer);
				playerB.render(gRenderer);	
				mainMap.mapShowing(gRenderer);
				
            	if (timeflag) {
            		gameScene->renderTimer(); // Render the timer
				}	
			}
			else if (stage == setting) {
				//settingUpdate
				settingScene->sceneRender(gRenderer);
				//render volume
				volume.renderVolume();
			}
			else if (stage == over) {
				overScene->sceneRender(gRenderer);
			}
			else {
				cout << "Stage error!\n";
			}
            //Update screen
            SDL_RenderPresent( gRenderer );
        }
    }

    // Free resources and close SDL
    close();

    return 0;
}































