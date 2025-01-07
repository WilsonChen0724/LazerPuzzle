#pragma once

#include "scene.h"
#include "Button.h"
#include <vector>
#include <string>

class Over : public scene {
private:
    
    TTF_Font* font;                            // Font for rendering descriptions
	SDL_Color textColor;
    
public:
	Info(SDL_Renderer* renderer, const std::string& bgImagePath, int bnum, Button* buttons, int* assignButtons, int assignLength, TTF_Font* font, SDL_Color textColor);
    ~Info();

    void InfoRender(SDL_Renderer* renderer);  // Render the scene
    void handleEvent(SDL_Event& e, int mouseX, int mouseY);          // Handle button clicks and navigation
};