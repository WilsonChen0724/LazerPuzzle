#include "Button.h"
// Default Constructor
Button::Button() : isHovered(false) {}

// Consructor
Button::Button(SDL_Renderer* renderer, const std::string& defaultImage, const std::string& hoverImage, int x, int y, int w, int h)
    : renderer(renderer), isHovered(false), defaultImagePath(defaultImage), hoverImagePath(hoverImage) {
    rect = {x, y, w, h};
	
    // Load textures
    if (!defaultTexture.loadFromFile(renderer, defaultImage)) {
    	std::cout << "Fail to load default image!\n";
	}
	if (!hoverTexture.loadFromFile(renderer, hoverImage)) {
		std::cout << "Fail to load hover image!\n";
	}
}
// Destructor
Button::~Button() {
    defaultTexture.free();
    hoverTexture.free();
}

//Copy constructor
Button::Button(const Button& b)
    : isHovered(b.isHovered), 
      defaultImagePath(b.defaultImagePath), hoverImagePath(b.hoverImagePath) {
    rect = b.rect;
	renderer = b.renderer; // 額外加這一行 
    // Reload textures using the stored renderer and image paths
    defaultTexture.loadFromFile(b.renderer, defaultImagePath);  				// 改renderer成b.renderer
    hoverTexture.loadFromFile(b.renderer, hoverImagePath);
}

// Check if the mouse is hovering over the button
void Button::checkHover(int mouseX, int mouseY) {
    isHovered = (mouseX > rect.x && mouseX < rect.x + rect.w &&
                 mouseY > rect.y && mouseY < rect.y + rect.h);
}

// Render the button
void Button::render(SDL_Renderer* InputRenderer) {
   if (isHovered) {
        if (hoverTexture.getTexture() == nullptr) {
            printf("Hover texture is null!\n");
        } else {
            hoverTexture.renderOrigin(rect.x, rect.y, renderer);
        }
    } else {
            defaultTexture.renderOrigin(rect.x, rect.y, renderer);
    }
}

// Check if the button is clicked
bool Button::isClicked(SDL_Event e) {
    return isHovered && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT;
}
int Button::getRectX() {
	return rect.x;
}
int Button::getRectY() {
	return rect.y;
}



// ButtonPair
ButtonPair::ButtonPair()
    : value(0), interval(1), lowerBound(0), upperBound(100), font(nullptr), textColor({0, 0, 0, 255}) {
    // Buttons are left uninitialized; ensure they are properly initialized before use
}

ButtonPair::ButtonPair(SDL_Renderer* renderer, const std::string& buttonLeftDefault, const std::string& buttonLeftHover,
                       const std::string& buttonRightDefault, const std::string& buttonRightHover,
                       SDL_Rect buttonLeftRect, SDL_Rect buttonRightRect,
                       int initialValue, int interval, int lowerBound, int upperBound,
                       TTF_Font* font, SDL_Color textColor)
    : buttonLeft(renderer, buttonLeftDefault, buttonLeftHover, buttonLeftRect.x, buttonLeftRect.y, buttonLeftRect.w, buttonLeftRect.h),
      buttonRight(renderer, buttonRightDefault, buttonRightHover, buttonRightRect.x, buttonRightRect.y, buttonRightRect.w, buttonRightRect.h),
      value(initialValue), interval(interval), lowerBound(lowerBound), upperBound(upperBound),
      font(font), textColor(textColor) {
    if (value < lowerBound || value > upperBound) {
        value = lowerBound; // Initialize value within bounds
        printf("Invalid value input, initialize by lower bound.");
    }
}

ButtonPair::~ButtonPair() {
    // No need to delete `font` here, as it is typically managed externally.
    // Ensure that Button class destructors are properly implemented to free SDL_Texture or other resources.
}

void ButtonPair::PairRender(SDL_Renderer* renderer) {
    // Render both buttons
    buttonLeft.render(renderer);
    buttonRight.render(renderer);

    // Calculate the midpoint between the two buttons
    int midX = (buttonLeft.rect.x + buttonRight.rect.x + buttonRight.rect.w) / 2;
    int midY = buttonLeft.rect.y + (buttonLeft.rect.h / 2);

    // Convert the value to a string
    std::string valueText = std::to_string(value);

    // Render the text at the midpoint
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, valueText.c_str(), textColor);
    if (textSurface) {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect textRect = {midX - (textSurface->w / 2), midY - (textSurface->h / 2), textSurface->w, textSurface->h};

        // Render the text
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        // Clean up resources
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    } else {
        printf("Failed to render text: %s\n", TTF_GetError());
    }
}

void ButtonPair::checkButtonPairHover(int mouseX, int mouseY) {
    // Check hover state for both buttons
    buttonLeft.checkHover(mouseX, mouseY); // ButtonLeft is hovered
    buttonRight.checkHover(mouseX, mouseY); // ButtonRight is hovered
}

bool ButtonPair::handleClick(SDL_Event& e) {
    if (buttonLeft.isClicked(e)) {
        value = std::max(lowerBound, value - interval); // Decrease value, stay within bounds
        printf("Left button clicked. Value: %d\n", value);
        return true; // A button was clicked
    } else if (buttonRight.isClicked(e)) {
        value = std::min(upperBound, value + interval); // Increase value, stay within bounds
        printf("Right button clicked. Value: %d\n", value);
        return true; // A button was clicked
    }
    return false; // No button clicked
}

int ButtonPair::getValue() const {
    return value;
}

int ButtonPair::getLeftButtonX() {
	return buttonLeft.getRectX();
}

int ButtonPair::getLeftButtonY() {
	return buttonLeft.getRectY();	
}
int ButtonPair::getRightButtonX() {
	return buttonRight.getRectX();
}

int ButtonPair::getRightButtonY() {
	return buttonRight.getRectY();	
}
