#include "Game.h"

Game::Game(SDL_Renderer* renderer, const std::string& bgImagePath, int bnum, Button* buttons, int* assignButtons, int assignLength,
           TTF_Font* font, SDL_Color color, int timerX, int timerY, int timerW, int timerH)
    : scene(renderer, bgImagePath, bnum, buttons, assignButtons, assignLength) {
    // Initialize the timer
    gameTimer = new LTimer(renderer, font, color, timerX, timerY, timerW, timerH);
	assignedTime = 180;
	
    // Initialize inventory positions and sizes
    leftInventoryRect = {150, 450, 250, 150};  // Bottom-left inventory
    rightInventoryRect = {1080, 450, 250, 150}; // Bottom-right inventory


    // Initialize inventory background textures
    if (!bottomLeftInventory.loadFromFile(renderer, "source/item_inventory.png")) {
        printf("Failed to load bottom-left inventory background!\n");
    }
    if (!bottomRightInventory.loadFromFile(renderer, "source/item_inventory.png")) {
        printf("Failed to load bottom-right inventory background!\n");
    }
    
    // Initialize items
 	if (!item11.loadFromFile(renderer, "source/state11.png")) {
        printf("Failed to load state11.png!\n");
    }
    if (!item12.loadFromFile(renderer, "source/state12.png")) {
        printf("Failed to load state12.png!\n");
    }
    if (!item13.loadFromFile(renderer, "source/state13.png")) {
        printf("Failed to load state13.png!\n");
    }
    if (!item14.loadFromFile(renderer, "source/state14.png")) {
        printf("Failed to load state14.png!\n");
    }
}

Game::~Game() {
    delete gameTimer;
}

// Render the scene
void Game::GameRender(SDL_Renderer* renderer) {
    // Render background without fade-in
    background.renderOrigin(0, 0, renderer);
        

    // Render buttons
    for (int i = 0; i < buttonNumber; i++) {
        buttons[i].render(renderer);
    }
    
    // Render bottom-left inventory background
    bottomLeftInventory.renderOrigin(leftInventoryRect.x, leftInventoryRect.y, renderer);

    // Render items in bottom-left inventory without modifying the queue (by copy a temp queue)
    std::queue<int> tempQueue = leftItems;
    int slot = 0;
    while (!tempQueue.empty()) {
        SDL_Rect itemRect = {leftInventoryRect.x, leftInventoryRect.y + (50 * slot), 50, 50};  
        switch (tempQueue.front()) {
        	case 11:
        		item11.render(itemRect.x, itemRect.y, itemRect.w, itemRect.h,renderer);
        		break;
        	case 12:
        		item12.render(itemRect.x, itemRect.y, itemRect.w, itemRect.h,renderer);
        		break;
        	case 13:
        		item13.render(itemRect.x, itemRect.y, itemRect.w, itemRect.h,renderer);
        		break;
        	case 14:
        		item14.render(itemRect.x, itemRect.y, itemRect.w, itemRect.h,renderer);
        		break;
        	default:
    			std::cout<< "Queue assign picture index out of range!\n"; 
		}
        tempQueue.pop();
        ++slot;
    }

    // Render bottom-right inventory background
    bottomRightInventory.renderOrigin(rightInventoryRect.x, rightInventoryRect.y, renderer);

    // Render items in bottom-right inventory without modifying the queue
    slot = 0;
    tempQueue = rightItems;
    while (!tempQueue.empty()) {
        SDL_Rect itemRect = {rightInventoryRect.x, rightInventoryRect.y + (50 * slot), 50, 50}; 
        switch (tempQueue.front()) {
            case 11:
        		item11.render(itemRect.x, itemRect.y, itemRect.w, itemRect.h,renderer);
        		break;
        	case 12:
        		item12.render(itemRect.x, itemRect.y, itemRect.w, itemRect.h,renderer);
        		break;
        	case 13:
        		item13.render(itemRect.x, itemRect.y, itemRect.w, itemRect.h,renderer);
        		break;
        	case 14:
        		item14.render(itemRect.x, itemRect.y, itemRect.w, itemRect.h,renderer);
        		break;
        	default:
    			std::cout<< "Queue assign picture index out of range!\n"; 
		}	
        tempQueue.pop();
        ++slot;
    }
}

void Game::startTimer() {
    if (assignedTime > 0) {
        gameTimer->start(assignedTime); // Start the timer from assigned time
        printf("Timer started with %d seconds.\n", assignedTime);
    } else {
        printf("No valid assigned time to start the timer.\n");
    }
}

void Game::stopTimer() {
    if (gameTimer) {
        gameTimer->stop();
    }
}

void Game::renderTimer() {
    if (gameTimer && gameTimer->isRunning()) {
        gameTimer->render();
    }
}

void Game::setAssignedTime(int seconds) {
    if (seconds > 0) {
        assignedTime = seconds;
        printf("Assigned time for the timer: %d seconds\n", assignedTime);
    } else {
        printf("Invalid time. Assigned time must be greater than zero.\n");
    }
}

//the functions about inventory
//addItemToLeft 
void Game::addItemToLeft(const int itemIndex) {
    if (leftItems.size() >= maxSlots) {
        leftItems.pop(); // Remove the oldest item if the inventory is full
    }

    LTexture newItem;
    if (itemIndex >= 11 and itemIndex <= 14) {
        leftItems.push(itemIndex);
        printf("Item added to left inventory. Total items: %zu\n", leftItems.size());
    } else {
        printf("Failed to load item for left inventory!\n");
    }
}

//addItemToRight 
void Game::addItemToRight(const int itemIndex) {
    if (rightItems.size() >= maxSlots) {
        rightItems.pop(); // Remove the oldest item if the inventory is full
    }

    LTexture newItem;
    if (itemIndex >= 11 and itemIndex <= 14) {
        rightItems.push(itemIndex);
        printf("Item added to right inventory. Total items: %zu\n", rightItems.size());
    } else {
        printf("Failed to load item for right inventory!\n");
    }
}

//clearLeftItem
void Game::clearLeftItem() {
	while (!leftItems.empty()) {
		leftItems.pop();
	}
}

//clearRightItem
void Game::clearRightItem() {
	while (!rightItems.empty()) {
		rightItems.pop();
	}
}

//popLeftItem
void Game::popLeftItem() {
	leftItems.pop();
}
//popRightItem
void Game::popRightItem() {
	rightItems.pop();
}

//getRemainTime
int Game::getRemainTime() {
	return gameTimer->getRemainingTime();
} 
