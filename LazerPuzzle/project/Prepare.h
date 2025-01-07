#pragma once
#include "scene.h"
#include "Button.h"
#include <vector>
#include "Game.h"

class Prepare : public scene {
private:
	std::vector<ButtonPair> buttonPairs;  // Vector of ButtonPair objects
	std::vector<std::string> titles;     // Vector of titles for ButtonPairs
    LTexture maps[6]; // Fixed array for 6 maps         // Vector of maps
	
    TTF_Font* font;            // Font for rendering text
    SDL_Color textColor;       // Color of the text
    LTexture titleBackground;  //titleBackground
	int mapLength;
	
	std::vector<std::string> skillTexts;
	int currentMapIndex;       // Index of the currently displayed map  ///NOTE: SET PUBLIC FOR FURTHER USE IN GAME
	int lazerPeriodTime;
	int itemsEnable;
    int player1Skill;
    int player2Skill;
	int totalTime;
public:
	
    Prepare(SDL_Renderer* renderer, const std::string& bgImagePath, int bnum, Button* buttons, int* assignButtons, int assignLength, TTF_Font* font, SDL_Color textColor);
    ~Prepare();

    void PrepareRender(SDL_Renderer* renderer); // Render the scene with ButtonPairs
    void checkPairHover(int mouseX, int mouseY); //check ButtonPair hover
    void handleAdjust(SDL_Event& e, Game* gameScene);               // Handle events for ButtonPairs
    int getTotalTime();
    int getCMapIndex();
	int getLPT();
    bool getItemsEn();
    int getP1Skill();
    int getP2Skill();

};
