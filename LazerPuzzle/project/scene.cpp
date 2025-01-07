#include "scene.h"
//fade in and fade out
void fadeOut(SDL_Renderer* renderer, int duration) {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    for (int alpha = 0; alpha <= 255; alpha += (255 / duration)) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
        SDL_RenderFillRect(renderer, NULL); // Fill the entire screen
        SDL_RenderPresent(renderer);
        SDL_Delay(10); // Adjust delay for smoother effect
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE); // Reset blend mode
}

void fadeInPicture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* dstRect, int duration) {
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    for (int alpha = 0; alpha <= 255; alpha += (255 / duration)) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Clear screen with black
        SDL_RenderClear(renderer);

        // Set texture alpha
        SDL_SetTextureAlphaMod(texture, alpha);

        // Render the texture
        SDL_RenderCopy(renderer, texture, NULL, dstRect);

        SDL_RenderPresent(renderer);
        SDL_Delay(10); // Adjust for smoother effect
    }

    // Ensure texture is fully visible
    SDL_SetTextureAlphaMod(texture, 255);
}

//scene class
// Constructor
scene::scene(SDL_Renderer* renderer, const std::string& bgImagePath, int bnum, Button* buttons, int* assignButtons, int assignLength): 
	hasFadedIn(false){
    // Load the background image
    background.loadFromFile(renderer, bgImagePath);
    buttonNumber = bnum;
    this->buttons = new Button[buttonNumber]; // 要用雙重陣列嗎? 
    if (buttonNumber != assignLength) {
    	std::cout << "WARNING:The length of assign number doesn't fit the button number." << std::endl;
    	std::cout << "button number: " << bnum << std::endl;
		std::cout << "Assign number: " << assignLength << std::endl;
	}
    for (int i = 0; i < std::min(buttonNumber,assignLength); ++i) {
        this->buttons[i] = buttons[assignButtons[i]]; // Uses Button's copy constructor
    }
}

// Destructor
scene::~scene() {
    background.free();
    delete [] buttons;
}

// Render the scene
void scene::sceneRender(SDL_Renderer* renderer) {
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
}

// Check hover state for all buttons
void scene::checkHover(int mouseX, int mouseY) {
    for (int i=0; i<buttonNumber; i++) {
        buttons[i].checkHover(mouseX, mouseY);
    }
}

// Handle button clicks
int scene::handleClick(SDL_Event& e) {
    for (int i = 0; i < buttonNumber; ++i) {
        if (buttons[i].isClicked(e)) {
            return i; // Return the index of the clicked button
        }
    }
    return -1; // No button clicked
}
// Reset fade
void scene::resetFade() {
    hasFadedIn = false; // Reset fade-in flag
}
bool scene::getFaded() {
	return hasFadedIn;
}

//change background
void scene::changeBackground(SDL_Renderer* renderer, const std::string& bgImagePath) {
	background.loadFromFile(renderer, bgImagePath);
}
