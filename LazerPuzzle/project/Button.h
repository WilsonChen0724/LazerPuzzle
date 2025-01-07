#pragma once

#include <SDL.h>
#include "texture.h"
#include <SDL_ttf.h>

class Button {
private:
	LTexture defaultTexture;
    LTexture hoverTexture;    // Hover state texture
    bool isHovered;           // Hover state
    						  //there should be a inherited Ltexture called mTexture 
    SDL_Renderer* renderer;   // Renderer (now stored as a member) //no need because of global, need because of copy constructor
	std::string defaultImagePath; // Path to default texture
    std::string hoverImagePath;   // Path to hover texture

public:
    SDL_Rect rect;            // Position and size of the button rect public for a reason
	
	// Constructor and Destructor
    Button();
    Button(const Button& b);
    Button(SDL_Renderer* renderer, const std::string& defaultImage, const std::string& hoverImage, int x, int y, int w, int h);
    ~Button();

    // Public Methods
    void checkHover(int mouseX, int mouseY); // Check if the mouse is hovering over the button
    void render(SDL_Renderer* renderer);    // Render the button
    bool isClicked(SDL_Event e) ; // Check if the button is clicked
    int getRectX();
    int getRectY();
};

class ButtonPair {
private:
    Button buttonLeft;    // Left button
    Button buttonRight;   // Right button
    int value;            // The value stored
    int interval;         // Step size for value change
    int lowerBound;       // Minimum value
    int upperBound;       // Maximum value
    
    TTF_Font* font;       // Font for rendering text
    SDL_Color textColor;  // Color of the text

public:
	//Default Constructor
	ButtonPair();
    // Constructor
	ButtonPair(SDL_Renderer* renderer, const std::string& buttonLeftDefault, const std::string& buttonLeftHover,
               const std::string& buttonRightDefault, const std::string& buttonRightHover,
               SDL_Rect buttonLeftRect, SDL_Rect buttonRightRect,
               int initialValue, int interval, int lowerBound, int upperBound,
               TTF_Font* font, SDL_Color textColor);

    // Destructor
    ~ButtonPair();

    void PairRender(SDL_Renderer* renderer);    // Render both buttons
    void checkButtonPairHover(int mouseX, int mouseY); // Check which button is hovered
    bool handleClick(SDL_Event& e);          // Check which button is clicked
    int getValue() const;                   // Get the current value
    int getLeftButtonX();
    int getLeftButtonY();
    int getRightButtonX();
    int getRightButtonY();
};
