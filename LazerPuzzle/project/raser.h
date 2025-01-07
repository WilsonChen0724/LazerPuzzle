#pragma once
#include "map.h"
#include <vector>
#include <utility>
#include"timer.h"

struct playerblock{
	int x;
	int y;
	int shoot;
};


class raser{
	private:
		
		int x;
		int y;
		int state =2;
		std::vector <std::pair<int,int>> linex;
		std::vector <std::pair<int,int>> liney;
		bool stay = false;
	public:
		 raser(map &mp);
		 ~raser();
		 void preview(map &mp,SDL_Renderer* gRenderer );
		 void randomPick(map &mp);
		 void raserShoot(map &mp);
		 void raserShowing(map &mp,SDL_Renderer* gRenderer);
		 
	
	
};

class raserSystem{
	private:
		raser** raserPtr;
		RTimer shootCountdown;
		int number = 1;
		uint32_t interval = 3000;
		bool overTime = false;
		
	public:
		raserSystem(uint32_t I);
		~raserSystem();
		void chainCheck(map &mp,SDL_Renderer* gRenderer);
		void raserinit(map &mp);
		void numberChange(int N);
		void raserShoot(map &mp,SDL_Renderer* gRenderer);
		void playerItemPlaced(int y, int x);
		void timeLineRaser();
		void playerShoot(int y,int x,int turn);
		void intervalSet(uint32_t I);
		void reset();
		void overtime();
		friend bool operator!(const raserSystem& ras);
		
};

class raserPlayerBlock{
	private:
		int x;
		int y;
		int state;
		bool broke = false;
};



class timerRaser: public RTimer{
	private:
		playerblock control;
	public:
		timerRaser(int y, int x,int shoot);
		playerblock playerBlockReturn();
	
};