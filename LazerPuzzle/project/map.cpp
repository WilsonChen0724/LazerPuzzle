#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "map.h"


const char blockGraph[20][30]{
	"",
	"source/state1.png",
	"source/state2.png",
	"source/state3.png",
	"source/state4.png",
	"source/state5.png",
	"source/state6.png",
	"source/state7.png",
	"source/state8.png",
	"source/state9.png",
	"source/state10.png",
	"source/state11.png",//speed up
	"source/state12.png",//banana
	"source/state13.png",//raser block
	"source/state14.png",//blocking block
	"source/state15.png",//real banana
	"source/state16.png"
	
};


int map1[10][10][14]{
	//0
	{{0,0,0,2,0,1,0,0,1,0,2,0,0,0},
	{0,0,2,1,0,0,2,2,0,0,1,2,0,0},
	{0,2,1,0,0,1,0,0,1,0,0,1,2,0},
	{2,1,0,2,1,2,2,2,2,1,2,0,1,2},
	{0,2,2,0,2,0,1,1,0,2,0,2,2,0},
	{0,2,2,0,2,0,1,1,0,2,0,2,2,0},
	{2,1,0,2,1,2,2,2,2,1,2,0,1,2},
	{0,2,1,0,0,1,0,0,1,0,0,1,2,0},
	{0,0,2,1,0,0,2,2,0,0,1,2,0,0},
	{0,0,2,2,0,1,0,0,1,0,2,0,0,0}},
	//1
	{{0,0,2,2,0,2,2,2,2,0,2,2,2,2},
	{0,0,1,0,2,1,2,2,1,2,0,1,2,2},
	{2,1,1,2,0,1,0,0,1,0,2,1,1,2},
	{2,0,2,2,1,2,2,2,2,1,2,2,0,2},
	{0,1,2,0,2,0,1,1,0,2,0,2,1,0},
	{0,1,2,0,2,0,1,1,0,2,0,2,1,0},
	{2,0,2,2,1,2,2,2,2,1,2,2,0,2},
	{2,1,1,2,0,1,0,0,1,0,2,1,1,2},
	{2,2,1,0,2,1,2,2,1,2,0,1,0,0},
	{2,2,2,2,0,2,2,2,2,0,2,2,0,0}},
	///2
	{{0,0,2,2,1,2,2,2,2,2,2,2,2,2},
	{0,0,2,2,0,0,1,2,0,0,1,1,0,2},
	{2,1,2,0,0,1,0,0,1,0,0,2,1,2},
	{2,2,0,2,1,1,2,1,1,1,2,0,1,2},
	{2,2,1,0,2,0,2,2,0,2,0,1,2,2},
	{2,2,1,0,2,0,2,2,0,2,0,1,2,2},
	{2,1,0,2,1,1,1,2,1,1,2,0,2,2},
	{2,1,2,0,0,1,0,0,1,0,0,2,1,2},
	{2,0,1,1,0,0,2,1,0,0,2,2,0,0},
	{2,2,2,2,2,2,2,2,2,1,2,2,0,0}},
	//3
	{{0,0,2,2,2,2,2,2,2,2,2,2,2,2},
	{0,0,2,1,2,1,2,2,1,2,1,2,1,2},
	{2,2,2,2,0,2,2,2,2,0,2,0,2,2},
	{2,1,0,1,2,1,0,1,1,2,1,2,1,2},
	{2,2,0,1,0,2,2,0,1,0,2,0,1,2},
	{2,1,0,2,0,1,0,2,2,0,1,0,2,2},
	{2,1,2,1,2,1,1,0,1,2,1,0,1,2},
	{2,2,0,2,0,2,2,2,2,0,2,2,2,2},
	{2,1,2,1,2,1,2,2,1,2,1,2,0,0},
	{2,2,2,2,2,1,2,2,1,2,2,2,0,0}},
	//4
	{{0,0,2,2,2,2,2,2,2,2,2,2,2,2},
	{0,0,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,0,0},
	{2,2,2,2,2,2,2,2,2,2,2,2,0,0}},
	//5
	{{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0}}
};





block::block(){
}

block::~block(){
}
void block::itemNOT(bool tf){
	item = tf;
}

void block::itemRandom(SDL_Renderer* gRenderer){
	
	
	if(item){
		int itemNum = std::rand() %100;
	//	std::cout<<"item\n";
		if(itemNum > 70) state = 11;
		else if(itemNum > 40) state = 12;
		else if(itemNum > 30) state = 13;
		else state = 14;
		picture.loadFromFile(gRenderer,blockGraph[state]);
	}


}
void block::itemDropping(){
	itemDrop = true;
}

void block::selfHealing(SDL_Renderer* gRenderer){//
	if((state==3||state==5)&&!countdownx.isStarted()){
		countdownx.start();
	}
	if((state==4||state==5)&&!countdowny.isStarted()){
		countdowny.start();
	}
	if(countdownx.counter(healingTime)&&countdownx.isStarted()){
		if(state == 3){
			state = 0;
			picture.free();
			if(itemDrop){
				itemDrop = false;
				itemRandom( gRenderer);
				
			}
		}
		if(state == 5){
			state = 4;
		}
		countdownx.stop();
	}
	if(countdowny.counter(healingTime)&&countdowny.isStarted()){
		if(state == 4){
			state = 0;
			picture.free();
			if(itemDrop){
				itemDrop = false;
				itemRandom(gRenderer);
			}
		}
		if(state == 5){
			state = 3;
		}
		countdowny.stop();
	}

	
}

void block::xbroke(){
	countdownx.start();
}

void block::ybroke(){
	countdowny.start();
}

void  block::stateAssign(int s){
	state = s;
}
int block::stateG(){
	return state;
}
int block::sizeGet(){
	return size;
}
void block::stateChange(int i){
	state = i;
}

map::map(bool tf, int mp){
	mapN = mp;
	item = tf;
	for(int i=0;i<10;i++){
		for(int j=0;j<14;j++){
			mapBlock[i][j].itemNOT(item);
		}
	}
}
map::~map(){
	
}

void map::initialize(bool tf, int mp){
	mapN = mp;
	item = tf;
	for(int i=0;i<10;i++){
		for(int j=0;j<14;j++){
			mapBlock[i][j].itemNOT(item);
//			mapBlock[i][j].
		}
	}
	
	
}

block& map::getBlock(int i,int j){
	return mapBlock[i][j];
}


void map::mapBackRendering(SDL_Renderer* gRenderer){
	mapBackground.renderOrigin(leftBorder,upBorder,gRenderer);
}

void map::mapSetting(SDL_Renderer* gRenderer){
	int tmp[10][14];
	if(!mapBackground.loadFromFile(gRenderer,"source/map.png")){
		std::cout<<"map back ground failed\n";
	}
//	mapBackground.renderOrigin(240,60,gRenderer);
//	if(mapN == 1){
//		std::cout<<"yes";
		for(int i=0;i<10;i++){
			for(int j=0;j<14;j++){
				tmp[i][j]=map1[mapN][i][j];
			}
//			std::cout<<std::endl;
		}
			
//	}

	std::cout<<"map "<<mapN<<std::endl;
	for(int i=0;i<10;i++){
		for(int j=0;j<14;j++){
			mapBlock[i][j].stateAssign(tmp[i][j]);
		}
	}
}

void map::blockRendering(int i,int j,SDL_Renderer* gRenderer){
	if(mapBlock[i][j].stateG()){
		if( !mapBlock[i][j].picture.loadFromFile( gRenderer,blockGraph[mapBlock[i][j].stateG()]))
	    {
	        printf( "Failed to load block texture!\n" );
	        
	    }
	}
}


bool map::mapRendering(SDL_Renderer* gRenderer){
	bool success = true;
	for(int i=0;i<10;i++){
		for(int j=0;j<14;j++){
			if(mapBlock[i][j].stateG()){
				if( !mapBlock[i][j].picture.loadFromFile( gRenderer,blockGraph[mapBlock[i][j].stateG()]))
			    {
			        printf( "Failed to load block texture!\n" );
			        success = false;
			    }
			}

		}
	}
	return success;
}

void map::mapShowing(SDL_Renderer* gRenderer){
	for(int i=0;i<10;i++){
		for(int j=0;j<14;j++){
			int x = leftBorder + mapBlock[i][j].sizeGet()+j*mapBlock[i][j].sizeGet();
			int y = upBorder + mapBlock[i][j].sizeGet() + i*mapBlock[i][j].sizeGet();
			mapBlock[i][j].selfHealing(gRenderer);
			if(mapBlock[i][j].stateG() > 0) {
				mapBlock[i][j].picture.render(x,y,mapBlock[i][j].sizeGet(),mapBlock[i][j].sizeGet(),gRenderer);
			}else{
//				mapBlock[i][j].picture.free();
//				mapBlock[i][j].picture.render(x,y,mapBlock[i][j].sizeGet(),mapBlock[i][j].sizeGet(),gRenderer);
			}
		}
	}
}
