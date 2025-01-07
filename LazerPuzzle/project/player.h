#pragma once

#include "texture.h"
#include "map.h"
#include <queue>
#include "timer.h"
#include "raser.h"
#include "Game.h"



class player {
	protected:
		
		int Ospeed = 20;
		int item;
		int power;
		int turn =0;// %4 0 up 1 right 2 down 3 left
		int playerState = 0;
		int skill = 0;
		int x;
		int y;
		int playerSize = 50;
		int state = 4;
		int speedP = 1;
		int blockX;
		int blockY;
		bool alive = true;
		bool itemPlaced = false;
		int32_t cooltime;
		RTimer shootTimer;
		RTimer skillTimer;
		RTimer undeadTimer;
		RTimer killTimer;
		RTimer speedTimer;
		RTimer caughtTimer;
		int32_t shottime = 1500;
		int32_t undeadtime = 3000;
		int32_t killtime = 3000;
		int32_t caughttime = 1000;
		int32_t speedtime = 3000;
		RTimer itemP;
		int itemX =-1;
		int itemY =-1;
		int itemTurn;
		int itemState = 0;
		std::queue <int> addItem;
		RTimer bananaTime;
		RTimer raserTime;
		RTimer bananaTimeStep;
		bool crazy = false;
		//int moveCnt ;
	public:
		LTexture picture;
		player(int Skill);
		~player();
		void move(map &mp);
		void itemGet(map &mp,SDL_Renderer* gRenderer);
		void itemReturn(map &mp);
		bool isAlive();
		void aliveDetect(map &mp,SDL_Renderer* gRenderer);
	 	void render( SDL_Renderer* gRenderer);
	 	void blockPos();
	 	void loadStatus(SDL_Renderer* gRenderer);
	 	void playerRender(SDL_Renderer* gRenderer);
	 	virtual void reset();
		int xreturn();
		int yreturn();
		int turnreturn();
		int statereturn();
		void xassign(int X);
		void yassign(int Y);
		void turnassign(int Turn);
		void stateassign(int State);
		void speedPassign(int P);
		void kill();
		void skillset();
		void skillAssign(int S);
		player& operator++();
		void crazyAssign(bool c);
	
};
class player2;

class player1:public player{
	public:
	player1(int Skill);
	~player1();
 	void pollEvents(SDL_Event &event,map &mp,raserSystem &rasSys,SDL_Renderer* gRenderer,player2 &anotherPlayer) ; 
	void skillusing(map &mp,player2 &anotherPlayer); 
	void skilldetect(map &mp,SDL_Renderer* gRenderer,player2 &anotherPlayer);
	void itemShow(Game* gameScene);
	void reset();
};

class player2:public player{
	public:
	player2(int Skill);
	~player2();
 	void pollEvents(SDL_Event &event,map &mp,raserSystem &rasSys,SDL_Renderer* gRenderer, player1 &anotherPlayer) ;
	void skillusing(map &mp,player1 &anotherPlayer); 
	void skilldetect(map &mp,SDL_Renderer* gRenderer,player1 &anotherPlayer);
	void itemShow(Game* gameScene);
	void reset();
};

