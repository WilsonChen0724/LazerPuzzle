#pragma once

#include <SDL.h>
#include "Button.h"
#include "texture.h"
void fadeInPicture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* dstRect, int duration);
void fadeOut(SDL_Renderer* renderer, int duration);
class scene {
	protected:
		LTexture background;
		Button *buttons;
		int buttonNumber;
		bool hasFadedIn;           // Flag to track fade-in status
		//SDL_Renderer* renderer;
	public:
	    // Constructor and Destructor
	    scene(SDL_Renderer* renderer, const std::string& bgImagePath, int bnum, Button* buttons, int* assignButtons, int assignLength);
	    ~scene();
	
	    // Public Methods
	    void sceneRender(SDL_Renderer* renderer);                     // Render the scene
	    void checkHover(int mouseX, int mouseY);  // Check hover state for all buttons
	    int handleClick(SDL_Event& e);     // Handle button clicks
		void resetFade(); // Reset the fade-in flag
		bool getFaded();
		void changeBackground(SDL_Renderer* renderer, const std::string& bgImagePath);
};
