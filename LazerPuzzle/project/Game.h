#pragma once
#include "scene.h"
#include "timer.h"
#include <queue> 

class Game : public scene {
private:
           // Timer for the game
	int assignedTime; // Stores the time assigned for the countdown
	
 	LTexture bottomLeftInventory;             // Background texture for bottom-left inventory
    LTexture bottomRightInventory;            // Background texture for bottom-right inventory

    std::queue<int> leftItems;           // Queue for bottom-left inventory items
    std::queue<int> rightItems;          // Queue for bottom-right inventory items

    SDL_Rect leftInventoryRect;               // Position and size for bottom-left inventory
    SDL_Rect rightInventoryRect;              // Position and size for bottom-right inventory
    
    LTexture item11;			//maybe const?
    LTexture item12;
    LTexture item13;
    LTexture item14;    
    
	const int maxSlots = 5;
	LTimer* gameTimer;
		
public:
    Game(SDL_Renderer* renderer, const std::string& bgImagePath, int bnum, Button* buttons, int* assignButtons, int assignLength, 
         TTF_Font* font, SDL_Color color, int timerX, int timerY, int timerW, int timerH);
    ~Game();

    void GameRender(SDL_Renderer* renderer); // Custom render
    void startTimer();                                    // Start the timer
    void stopTimer();                                                // Stop the timer
    void renderTimer();                                              // Render the timer
    void setAssignedTime(int seconds); // Assign time for the countdown
    
    void loadInventoryImages(SDL_Renderer* renderer, const std::string& Path);
    void addItemToLeft(const int itemIndex);
    void addItemToRight(const int itemIndex);
    void renderInventories(SDL_Renderer* renderer); // This will now be integrated into `Game::render`
    void clearLeftItem();
    void clearRightItem();
    void popLeftItem();
    void popRightItem();
    int getRemainTime();
};
