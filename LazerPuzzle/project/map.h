#pragma once

#include "texture.h"
#include "timer.h"

static const int leftBorder = 240;
static const int rightBorder = 1040;
static const int upBorder = 80;
static const int downBorder = 680;

class block{
	private:
		int state = 0;
		int size = 50;
		RTimer countdownx;
		RTimer countdowny;
		uint32_t healingTime = 1000;
		bool itemDrop = false;
		bool item = false;
	public:
		LTexture picture;
		void stateAssign(int state);
		void selfHealing(SDL_Renderer* gRenderer);//SDL_Renderer* gRenderer
		void itemRandom(SDL_Renderer* gRenderer);
		void itemDropping();
		void xbroke();
		void ybroke();
		int stateG();
		int sizeGet();
		void stateChange(int i);
		void itemNOT(bool tf);
		block();
		~block();
	
	
};


class map{
	
	private:	
		block mapBlock[10][14];
		bool item = false;
		int mapN;
		LTexture mapBackground;
	public:
		void mapSetting(SDL_Renderer* gRenderer);
		bool mapRendering(SDL_Renderer* gRenderer);
		void mapShowing(SDL_Renderer* gRenderer);
		void blockRendering(int i,int j,SDL_Renderer* gRenderer);
		void mapBackRendering(SDL_Renderer* gRenderer);
		void selfHealing();
		block& getBlock(int i,int j);
		void initialize(bool tf, int mp);
		map(bool tf, int mp);
		~map();
};