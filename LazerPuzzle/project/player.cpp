#include"player.h"
#include<SDL.h>
#include <iostream>
#include "map.h"
#include "raser.h"
#include <vector>


const char playerGraph[33][30]{
	"source/player0.png",//no skill
	"source/player1.png",
	"source/player2.png",
	"source/player3.png",
	"source/player4.png",//
	"source/player5.png",
	"source/player6.png",
	"source/player7.png",
	"source/player8.png",//
	"source/player9.png",
	"source/player10.png",
	"source/player11.png",
	"source/player12.png",//
	"source/player13.png",
	"source/player14.png",
	"source/player15.png",
	"source/player16.png",
	"source/player17.png",
	"source/player18.png",
	"source/player19.png",
	"source/player20.png",
	"source/player21.png",
	"source/player22.png",
	"source/player23.png",
	"source/player24.png",
	"source/player25.png",
	"source/player26.png",
	"source/player27.png",
	"source/player28.png",
	"source/player29.png",
	"source/player30.png",
	"source/player31.png",
	"source/player32.png"
	
};
player::player(int Skill){
	skill = Skill;
	playerState = skill*4;
	skillset();
	
}
player::~player(){
	//free(); 
}


//
player& player::operator++() {
    skill = std::rand()%6+1;
    cooltime = 1000;
    return *this;
}

void player::reset(){
		shootTimer.stop();
		skillTimer.stop();
		undeadTimer.stop();
		killTimer.stop();
		speedTimer.stop();
		caughtTimer.stop();
		turn =0;// %4 0 up 1 right 2 down 3 left
		playerState = 0;
		Ospeed = 20;
		speedP = 1;
		alive = true;
		itemPlaced = false;
		itemX =-1;
		itemY =-1;
		itemState = 0;
		while(!addItem.empty())addItem.pop();
		bananaTime.stop();
		raserTime.stop();
		bananaTimeStep.stop();
}

void player1::reset(){
		shootTimer.stop();
		skillTimer.stop();
		undeadTimer.stop();
		killTimer.stop();
		speedTimer.stop();
		caughtTimer.stop();
		turn =0;// %4 0 up 1 right 2 down 3 left
		playerState = 0;
		Ospeed = 20;
		speedP = 1;
		alive = true;
		itemPlaced = false;
		itemX =-1;
		itemY =-1;
		itemState = 0;
		while(!addItem.empty())addItem.pop();
		bananaTime.stop();
		raserTime.stop();
		bananaTimeStep.stop();
		x = leftBorder +playerSize;
		y = upBorder +playerSize;
}


void player2::reset(){
		shootTimer.stop();
		skillTimer.stop();
		undeadTimer.stop();
		killTimer.stop();
		speedTimer.stop();
		caughtTimer.stop();
		turn =0;// %4 0 up 1 right 2 down 3 left
		playerState = 0;
		Ospeed = 20;
		speedP = 1;
		alive = true;
		itemPlaced = false;
		itemX =-1;
		itemY =-1;
		itemState = 0;
		while(!addItem.empty())addItem.pop();
		bananaTime.stop();
		raserTime.stop();
		bananaTimeStep.stop();
		x =  rightBorder -2*playerSize;
		y = downBorder -2*playerSize;
}


void player1::itemShow(Game* gameScene){
	int size = addItem.size();
	int tmp;
	gameScene->clearLeftItem();
	
	for(int i=0;i<size;i++){
		tmp = addItem.front();
		addItem.pop();
		gameScene->addItemToLeft(tmp);
		addItem.push(tmp);
	}
}

void player2::itemShow(Game* gameScene){
	int size = addItem.size();
	int tmp;
	
	gameScene->clearRightItem();
	
	for(int i=0;i<size;i++){
		tmp = addItem.front();
		addItem.pop();
		gameScene->addItemToRight(tmp);
		addItem.push(tmp);
	}
}


void  player::skillAssign(int S){
	skill = S;
	playerState = skill*4;
	if(crazy){
		cooltime = 1500;
	}else{
		skillset();
	}
	
		
	           
}
	           
void player::loadStatus(SDL_Renderer* gRenderer){
	if(!picture.loadFromFile(gRenderer,playerGraph[playerState])){
		std::cout<<"player graph failed\n";
	}
}

void player::render( SDL_Renderer* gRenderer){
	picture.render(x,y,playerSize,playerSize,gRenderer);
}


void player::aliveDetect(map &mp,SDL_Renderer* gRenderer){
	if(itemP.counter(500))itemP.stop();

	int tmpx = (x - leftBorder)%playerSize;
	int tmpy = (y - upBorder)%playerSize;
	
	if(tmpx){
		if(mp.getBlock(blockY,blockX+1).stateG() == 3 ||mp.getBlock(blockY,blockX+1).stateG() == 4||mp.getBlock(blockY,blockX+1).stateG() == 5 ){
			alive = false;
			
		}else if(mp.getBlock(blockY,blockX+1).stateG() == 15 ){
			speedP = 5;
			bananaTimeStep.start();
		}
		if(mp.getBlock(blockY,blockX).stateG() == 3 ||mp.getBlock(blockY,blockX).stateG() == 4||mp.getBlock(blockY,blockX).stateG() == 5 ){
			alive = false;
		}else if(mp.getBlock(blockY,blockX).stateG() == 15 ){
			speedP = 5;
			bananaTimeStep.start();
		}		
	}else if(tmpy){
		if(mp.getBlock(blockY+1,blockX).stateG() == 3 ||mp.getBlock(blockY+1,blockX).stateG() == 4||mp.getBlock(blockY+1,blockX).stateG() == 5 ){
			alive = false;
		}else if(mp.getBlock(blockY+1,blockX).stateG() == 15 ){
			speedP = 5;
			bananaTimeStep.start();
		}
		if(mp.getBlock(blockY,blockX).stateG() == 3 ||mp.getBlock(blockY,blockX).stateG() == 4||mp.getBlock(blockY,blockX).stateG() == 5 ){
			alive = false;
		}else if(mp.getBlock(blockY,blockX).stateG() == 15 ){
			speedP = 5;
			bananaTimeStep.start();
		}
	}else{
		if(mp.getBlock(blockY,blockX).stateG() == 3 ||mp.getBlock(blockY,blockX).stateG() == 4||mp.getBlock(blockY,blockX).stateG() == 5 ){
			alive = false;
		}else if(mp.getBlock(blockY,blockX).stateG() == 15 ){
			speedP = 5;
			bananaTimeStep.start();
		}
	}
	if(speedTimer.counter(speedtime))speedTimer.stop();
	if(!bananaTime.counter(1000)&&bananaTime.isStarted()){
		speedP=1;
		speedTimer.stop();
	}else{
		bananaTime.stop();
	}
	if(bananaTimeStep.counter(3000)){
		speedP=1;
		bananaTimeStep.stop();
	}

	if(undeadTimer.isStarted()){
		playerState = 31;//alive detect state
//		loadStatus(gRenderer);
		alive = true;
	}

}



player1::player1(int Skill): player(Skill){
	x =  leftBorder +playerSize;
	y = upBorder +playerSize;
}

player1::~player1(){
}

void player::blockPos(){
	blockX = (x-leftBorder) /playerSize - 1;
	blockY = (y-upBorder) /playerSize - 1;
//	std::cout <<blockX <<" "<<blockY<<std::endl;
}

bool player::isAlive(){
	if(!alive)picture.free();

	if(!addItem.empty()){
		std::cout<<addItem.front()<<"\n";
	}
	
	return alive;
}

void player::itemReturn(map &mp){
	if(mp.getBlock(itemY,itemX).stateG()!= itemState){
		itemX = -1;
		itemY = -1;
		itemPlaced = false;
		shootTimer.stop();
		itemState  = 0;
	}
}


void player::itemGet(map &mp, SDL_Renderer* gRenderer){
	int tmpx = (x - leftBorder)%playerSize;
	int tmpy = (y - upBorder)%playerSize;
	
	if(tmpx){
		if(mp.getBlock(blockY,blockX+1).stateG() <15 &&mp.getBlock(blockY,blockX+1).stateG() > 10 ){
			if(addItem.size()>4)addItem.pop();
			addItem.push(mp.getBlock(blockY,blockX+1).stateG());
			mp.getBlock(blockY,blockX+1).stateAssign(0);
//			mp.blockRendering(blockY,blockX+1,gRenderer);
		}
		if(mp.getBlock(blockY,blockX).stateG()  < 15  &&mp.getBlock(blockY,blockX).stateG() > 10){
			if(addItem.size()>4)addItem.pop();
			addItem.push(mp.getBlock(blockY,blockX).stateG());
			mp.getBlock(blockY,blockX).stateAssign(0);
//			mp.blockRendering(blockY,blockX,gRenderer);
		}		
	}else if(tmpy){
		if(mp.getBlock(blockY+1,blockX).stateG() < 15 &&mp.getBlock(blockY+1,blockX).stateG() > 10 ){
			if(addItem.size()>4)addItem.pop();
			addItem.push(mp.getBlock(blockY+1,blockX).stateG());
			mp.getBlock(blockY+1,blockX).stateAssign(0);
//			mp.blockRendering(blockY+1,blockX,gRenderer);
		}
		if(mp.getBlock(blockY,blockX).stateG() <15 &&mp.getBlock(blockY,blockX).stateG() > 10 ){
			if(addItem.size()>4)addItem.pop();
			addItem.push(mp.getBlock(blockY,blockX).stateG());
			mp.getBlock(blockY,blockX).stateAssign(0);
//			mp.blockRendering(blockY,blockX,gRenderer);
		}
	}else{
		if(mp.getBlock(blockY,blockX).stateG() < 15  &&mp.getBlock(blockY,blockX).stateG() > 10 ){
			if(addItem.size()>4)addItem.pop();
			addItem.push(mp.getBlock(blockY,blockX).stateG());
			mp.getBlock(blockY,blockX).stateAssign(0);
//			mp.blockRendering(blockY,blockX,gRenderer);
		}
	}
	
	
}

void player::skillset(){
	if(skill==1){
		cooltime = 10000;//dash
	}
	if(skill==2){
		cooltime = 20000;//invisisble
	}
	if(skill==3){
		cooltime = 30000;//kill 
	}
	if(skill==4){
		cooltime = 15000;//close
	}
	if(skill==5){
		cooltime = 10000;//swap
	}
	if(skill==6)
		cooltime = 20000;//cauhgt
}

int player::xreturn(){
	return x;
}
int player::yreturn(){
	return y;
}

int player::turnreturn(){
	return turn;
}
int player::statereturn(){
	return state;
}

void player::xassign(int X){
	x = X;
}
void player::yassign(int Y){
	y = Y;
}
void player::turnassign(int Turn){
	turn = Turn;
}
void player::stateassign(int State){
	state = State;
}
	
void player::kill(){
	alive =false;
}
void player::speedPassign(int P){
	speedP = P;
}
void player1::skillusing(map &mp,player2 &anotherPlayer){
	
//	
	if(skill == 1){
		skillTimer.start();
		int tmpy = blockY,tmpx = blockX;
		if(turn == 0){
			while(!((mp.getBlock(tmpy,tmpx).stateG()==1||mp.getBlock(tmpy,tmpx).stateG()==2)
				||(mp.getBlock(tmpy,tmpx).stateG()==6||mp.getBlock(tmpy,tmpx).stateG()==7)
				||(mp.getBlock(tmpy,tmpx).stateG()==8||mp.getBlock(tmpy,tmpx).stateG()==9))){
				tmpy--;
				if(tmpy<0){
					break;
				}
			}
			tmpy++;
		}
		if(turn == 1){
			while(!((mp.getBlock(tmpy,tmpx).stateG()==1||mp.getBlock(tmpy,tmpx).stateG()==2)
				||(mp.getBlock(tmpy,tmpx).stateG()==6||mp.getBlock(tmpy,tmpx).stateG()==7)
				||(mp.getBlock(tmpy,tmpx).stateG()==8||mp.getBlock(tmpy,tmpx).stateG()==9))){
				tmpx++;
				if(tmpx>13){
					
					break;
				}
			}
			tmpx--;		
		}
		if(turn == 2){
			while(!((mp.getBlock(tmpy,tmpx).stateG()==1||mp.getBlock(tmpy,tmpx).stateG()==2)
				||(mp.getBlock(tmpy,tmpx).stateG()==6||mp.getBlock(tmpy,tmpx).stateG()==7)
				||(mp.getBlock(tmpy,tmpx).stateG()==8||mp.getBlock(tmpy,tmpx).stateG()==9))){
				tmpy++;
				if(tmpy>9){
					
					break;
				}
			}	
			tmpy--;	
		}
		if(turn == 3){
			while(!((mp.getBlock(tmpy,tmpx).stateG()==1||mp.getBlock(tmpy,tmpx).stateG()==2)
				||(mp.getBlock(tmpy,tmpx).stateG()==6||mp.getBlock(tmpy,tmpx).stateG()==7)
				||(mp.getBlock(tmpy,tmpx).stateG()==8||mp.getBlock(tmpy,tmpx).stateG()==9))){
				tmpx--;
				if(tmpx<0){
					
					break;
				}
			}		
			tmpx++;
		}
		x = (tmpx)*playerSize+leftBorder+playerSize;
		y = tmpy*playerSize + playerSize+upBorder;
		state = 4;	
	}
	if(skill == 2){
		skillTimer.start();
		undeadTimer.start();
	}
	if(skill == 3){
		skillTimer.start();
		killTimer.start();
	}
	if(skill == 4){
		skillTimer.start();
		x = anotherPlayer.xreturn();
		y = anotherPlayer.yreturn();
		turn = anotherPlayer.turnreturn();
		state = anotherPlayer.statereturn();
		
	}
	if(skill == 5){
		if((x>anotherPlayer.xreturn()&&y==anotherPlayer.yreturn()&&turn==3&&anotherPlayer.turnreturn()==1)
		||(x<anotherPlayer.xreturn()&&y==anotherPlayer.yreturn()&&turn==1&&anotherPlayer.turnreturn()==3)
		||(x==anotherPlayer.xreturn()&&y>anotherPlayer.yreturn()&&turn==0&&anotherPlayer.turnreturn()==2)
		||(x==anotherPlayer.xreturn()&&y<anotherPlayer.yreturn()&&turn==2&&anotherPlayer.turnreturn()==0)){
			skillTimer.start();
			int tmpx = x;
			x = anotherPlayer.xreturn();
			anotherPlayer.xassign(tmpx);
			int tmpy = y;
			y = anotherPlayer.yreturn();
			anotherPlayer.yassign(tmpy);
			int tmpturn = turn;
			turn = anotherPlayer.turnreturn();
			anotherPlayer.turnassign(tmpturn);
			int tmpstate = state;
			state = anotherPlayer.statereturn();
			anotherPlayer.stateassign(tmpstate);
		}
			
	}
	if(skill == 6){
		int tmpy = blockY,tmpx = blockX;
		bool caught = false;
		skillTimer.start();
		if(turn == 0){
			while(!((mp.getBlock(tmpy,tmpx).stateG()==1||mp.getBlock(tmpy,tmpx).stateG()==2)
				||(mp.getBlock(tmpy,tmpx).stateG()==6||mp.getBlock(tmpy,tmpx).stateG()==7)
				||(mp.getBlock(tmpy,tmpx).stateG()==8||mp.getBlock(tmpy,tmpx).stateG()==9))){
				if(x==anotherPlayer.xreturn() &&tmpy==(anotherPlayer.yreturn()-(upBorder +playerSize))/playerSize){
					caught = true;
					break;
				} 
				tmpy--;
				if(tmpy<0){
					break;
				}
			}
			tmpy++;
		}
		if(turn == 1){
			while(!((mp.getBlock(tmpy,tmpx).stateG()==1||mp.getBlock(tmpy,tmpx).stateG()==2)
				||(mp.getBlock(tmpy,tmpx).stateG()==6||mp.getBlock(tmpy,tmpx).stateG()==7)
				||(mp.getBlock(tmpy,tmpx).stateG()==8||mp.getBlock(tmpy,tmpx).stateG()==9))){
				if(tmpx==(anotherPlayer.xreturn()-(leftBorder +playerSize))/playerSize &&y==anotherPlayer.yreturn()){
					caught = true;
					break;
				} 
				tmpx++;
				if(tmpx>13){
					
					break;
				}
			}
			tmpx--;		
		}
		if(turn == 2){
			while(!((mp.getBlock(tmpy,tmpx).stateG()==1||mp.getBlock(tmpy,tmpx).stateG()==2)
				||(mp.getBlock(tmpy,tmpx).stateG()==6||mp.getBlock(tmpy,tmpx).stateG()==7)
				||(mp.getBlock(tmpy,tmpx).stateG()==8||mp.getBlock(tmpy,tmpx).stateG()==9))){
				if(x==anotherPlayer.xreturn() &&tmpy==(anotherPlayer.yreturn()-(upBorder +playerSize))/playerSize){
					caught = true;
					break;
				} 
				tmpy++;
				if(tmpy>9){
					
					break;
				}
			}	
			tmpy--;	
		}
		if(turn == 3){
			while(!((mp.getBlock(tmpy,tmpx).stateG()==1||mp.getBlock(tmpy,tmpx).stateG()==2)
				||(mp.getBlock(tmpy,tmpx).stateG()==6||mp.getBlock(tmpy,tmpx).stateG()==7)
				||(mp.getBlock(tmpy,tmpx).stateG()==8||mp.getBlock(tmpy,tmpx).stateG()==9))){
				if(tmpx==((anotherPlayer.xreturn()-(leftBorder +playerSize))/playerSize) &&y==anotherPlayer.yreturn()){
					caught = true;
					break;
				} 
				tmpx--;
				if(tmpx<0){
					
					break;
				}
			}		
			tmpx++;
		}
		if(caught){
			anotherPlayer.xassign(x);
			anotherPlayer.yassign(y);
			anotherPlayer.turnassign(turn);
			anotherPlayer.stateassign(state);
			anotherPlayer.speedPassign(50);
			caughtTimer.start();
		}
	}
}
/***********************************************************************/
void player1::skilldetect(map &mp,SDL_Renderer* gRenderer,player2 &anotherPlayer){
	if(undeadTimer.counter(undeadtime))undeadTimer.stop();
	if(killTimer.counter(killtime)){
		killTimer.stop();
		speedP = 1;
	}
	if(killTimer.isStarted()){
		speedP = 15;
		if(abs(anotherPlayer.xreturn()-x)<5&&abs(anotherPlayer.yreturn()-y)<5&&!killTimer.counter(killtime)){
			
			anotherPlayer.kill();
		}
	}
	if(caughtTimer.counter(caughttime)){
		anotherPlayer.speedPassign(1);
		caughtTimer.stop();
	}
	if(skillTimer.counter(cooltime))skillTimer.stop();
}

void player::crazyAssign(bool c){
	crazy=c;
}

void player1::pollEvents(SDL_Event &event,map &mp,raserSystem &rasSys,SDL_Renderer* gRenderer,player2 &anotherPlayer){
//	std::cout<<speed;
	if(event.type == SDL_KEYDOWN){
			int speed = Ospeed/speedP;
			if(speedTimer.isStarted())speed=50;
			switch(event.key.keysym.sym){
			case SDLK_LEFT:
					if(state==1||state==3||state==4){
						
						if(turn!=3){
							turn =3;
							playerState = turn + skill*4;
							loadStatus(gRenderer);	
						}
						else if(x-speed>=leftBorder+playerSize){
							if(blockX>0){
								if((mp.getBlock(blockY,blockX-1).stateG()==1||mp.getBlock(blockY,blockX-1).stateG()==2)
									||(mp.getBlock(blockY,blockX-1).stateG()==6||mp.getBlock(blockY,blockX-1).stateG()==7)
									||(mp.getBlock(blockY,blockX-1).stateG()==8||mp.getBlock(blockY,blockX-1).stateG()==9))
								
								{
//									std::cout<<mp.getBlock(blockY,blockX-1).stateGet();
								int tmp = std::min(x-(blockX)*playerSize-leftBorder-playerSize,speed);
								if(!tmp)x-=tmp;
//								x-=std::min(x-(blockX)*playerSize-leftBorder-playerSize,speed);
								
								}else{
									x-=speed;
								}
							}
//							x-=speed;
							state = 3;
						}
					}
					break;
			case SDLK_RIGHT:
				if(state==1||state==3||state==4){
					if(turn!=1){
						turn =1;
						playerState = turn + skill*4;
						loadStatus(gRenderer);		
					}
					else if(x+speed<=rightBorder-2*playerSize){
							if(blockX<13){
								
								if((x-leftBorder)%playerSize==0&&((mp.getBlock(blockY,blockX+1).stateG()==1||mp.getBlock(blockY,blockX+1).stateG()==2)
									||(mp.getBlock(blockY,blockX+1).stateG()==6||mp.getBlock(blockY,blockX+1).stateG()==7)
									||(mp.getBlock(blockY,blockX+1).stateG()==8||mp.getBlock(blockY,blockX+1).stateG()==9))){
//									std::cout<<mp.getBlock(blockY,blockX-1).stateGet();
									int tmp = std::min((blockX+1)*playerSize-leftBorder-playerSize-x,speed);
									if(!tmp)x+=tmp;	
//									std::cout<<"111\n";
								}else if((x-leftBorder)%playerSize!=0&&((mp.getBlock(blockY,blockX+2).stateG()==1||mp.getBlock(blockY,blockX+2).stateG()==2)
									||(mp.getBlock(blockY,blockX+2).stateG()==6||mp.getBlock(blockY,blockX+2).stateG()==7)
									||(mp.getBlock(blockY,blockX+2).stateG()==8||mp.getBlock(blockY,blockX+2).stateG()==9)))	{
									int tmp = std::min((blockX+1)*playerSize+leftBorder+playerSize-x,speed);
									if(!tmp)x+=tmp; 
//									std::cout<<tmp<<"222\n";
//									system("pause");
								
								}else{
									x+=speed;
								}
								
								
							}
						state = 1;
					}
				}	
				break;
			case SDLK_UP:
				if(state==0||state==2||state==4){
					if(turn!=0){
						turn =0;
						playerState = turn + skill*4;
						loadStatus(gRenderer);		
					}
					else if(y-speed>=upBorder+playerSize){
							if(blockY){
								if((mp.getBlock(blockY-1,blockX).stateG()==1||mp.getBlock(blockY-1,blockX).stateG()==2)
									||(mp.getBlock(blockY-1,blockX).stateG()==6||mp.getBlock(blockY-1,blockX).stateG()==7)
									||(mp.getBlock(blockY-1,blockX).stateG()==8||mp.getBlock(blockY-1,blockX).stateG()==9)){
//									std::cout<<mp.getBlock(blockY,blockX-1).stateGet();
								int tmp = std::min(y-(blockY)*playerSize-upBorder-playerSize,speed);
								if(!tmp)y-=tmp;
//								x-=std::min(x-(blockX)*playerSize-leftBorder-playerSize,speed);
								
								}else{
									y-=speed;
								}
							}
						state = 0;
					}
				}
				break;
			case SDLK_DOWN:
				if(state==0||state==2||state==4){
					if(turn!=2){
						turn =2;	
						playerState = turn + skill*4;
						loadStatus(gRenderer);	
					}
					else if(y+speed<=downBorder-2*playerSize){
						if(blockY<11){
							if((y-upBorder)%playerSize==0&&(mp.getBlock(blockY+1,blockX).stateG()==1||mp.getBlock(blockY+1,blockX).stateG()==2)
									||(mp.getBlock(blockY+1,blockX).stateG()==6||mp.getBlock(blockY+1,blockX).stateG()==7)
									||(mp.getBlock(blockY+1,blockX).stateG()==8||mp.getBlock(blockY+1,blockX).stateG()==9)){
//									std::cout<<mp.getBlock(blockY,blockX-1).stateGet();
								int tmp = std::min((blockY+1)*playerSize-leftBorder-playerSize-y,speed);
								if(!tmp)y+=tmp;	
//									std::cout<<"111\n";
								}else if((y-upBorder)%playerSize!=0&&((mp.getBlock(blockY+2,blockX).stateG()==1||mp.getBlock(blockY+2,blockX).stateG()==2)
									||(mp.getBlock(blockY+2,blockX).stateG()==6||mp.getBlock(blockY+2,blockX).stateG()==7)
									||(mp.getBlock(blockY+2,blockX).stateG()==8||mp.getBlock(blockY+2,blockX).stateG()==9)))	{
									int tmp = std::min((blockY+1)*playerSize+upBorder+playerSize-y,speed);
									if(!tmp)y+=tmp; 
//									std::cout<<tmp<<"222\n";
//									system("pause");
								
								}else{
									y+=speed;
								}
							}
						state = 2;
					}
					
				}
				break;
				
			case SDLK_RSHIFT:
				if(!itemPlaced && state == 4){
					itemPlaced = true;
					shootTimer.start();
					itemX = blockX;
					itemY = blockY;
					if(turn == 0){
						mp.getBlock(blockY,blockX).stateAssign(6);
						itemState = 6;
					}
					if(turn == 1){
						mp.getBlock(blockY,blockX).stateAssign(7);
						itemState = 7;
					}
					if(turn == 2){
						mp.getBlock(blockY,blockX).stateAssign(8);
						itemState = 8;
					}
					if(turn == 3){
						mp.getBlock(blockY,blockX).stateAssign(9);
						itemState = 9;
					}		
					mp.blockRendering(blockY,blockX,gRenderer);				
				}else if(itemPlaced && shootTimer.counter(shottime)){
					if(itemState == 6&&itemY-1>-1)rasSys.playerShoot(itemY-1,itemX,itemState-6);
					if(itemState == 7&&itemX+1<14)rasSys.playerShoot(itemY,itemX+1,itemState-6);
					if(itemState == 8&&itemY+1<10)rasSys.playerShoot(itemY+1,itemX,itemState-6);
					if(itemState == 9&&itemX-1>-1)rasSys.playerShoot(itemY,itemX-1,itemState-6);
					mp.getBlock(itemY,itemX).stateAssign(0);
//					mp.blockRendering(itemY,itemX,gRenderer);
					itemY = -1;
					itemX = -1;
					itemState = 0;
					itemPlaced = false;
					shootTimer.stop();
				}
				break;
				
			case SDLK_RCTRL:
				if(state == 4){
					
					if((!itemP.isStarted())&&addItem.size()>0){
//						std::cout<<"enter\n";
						int tmp = addItem.front();
						itemP.start();
						addItem.pop();
						if(tmp == 11){
							speedTimer.start();
							bananaTime.stop();
							speedP = 1;
						}
						if(tmp == 12){
							mp.getBlock(blockY,blockX).stateAssign(15);
							bananaTime.start();
						}
						if(tmp==13){
							mp.getBlock(blockY,blockX).stateAssign(10);
							rasSys.playerItemPlaced(blockY,blockX);
							
						}
						if(tmp ==14){
							mp.getBlock(blockY,blockX).stateAssign(2);
						}
						
					}
					mp.blockRendering(blockY,blockX,gRenderer);				
				}
				break;
			 case SDLK_l:
			 	if((!skillTimer.isStarted())){
			 		std::cout<<"skill using";
			 		skillusing(mp,anotherPlayer);
//			 		if(crazy)++(*this);
				 }
			}
	}
		
		
}


void player2::skillusing(map &mp,player1 &anotherPlayer){
	
//	
	if(skill == 1){
		skillTimer.start();
		int tmpy = blockY,tmpx = blockX;
		if(turn == 0){
			while(!((mp.getBlock(tmpy,tmpx).stateG()==1||mp.getBlock(tmpy,tmpx).stateG()==2)
				||(mp.getBlock(tmpy,tmpx).stateG()==6||mp.getBlock(tmpy,tmpx).stateG()==7)
				||(mp.getBlock(tmpy,tmpx).stateG()==8||mp.getBlock(tmpy,tmpx).stateG()==9))){
				tmpy--;
				if(tmpy<0){
					break;
				}
			}
			tmpy++;
		}
		if(turn == 1){
			while(!((mp.getBlock(tmpy,tmpx).stateG()==1||mp.getBlock(tmpy,tmpx).stateG()==2)
				||(mp.getBlock(tmpy,tmpx).stateG()==6||mp.getBlock(tmpy,tmpx).stateG()==7)
				||(mp.getBlock(tmpy,tmpx).stateG()==8||mp.getBlock(tmpy,tmpx).stateG()==9))){
				tmpx++;
				if(tmpx>13){
					
					break;
				}
			}
			tmpx--;		
		}
		if(turn == 2){
			while(!((mp.getBlock(tmpy,tmpx).stateG()==1||mp.getBlock(tmpy,tmpx).stateG()==2)
				||(mp.getBlock(tmpy,tmpx).stateG()==6||mp.getBlock(tmpy,tmpx).stateG()==7)
				||(mp.getBlock(tmpy,tmpx).stateG()==8||mp.getBlock(tmpy,tmpx).stateG()==9))){
				tmpy++;
				if(tmpy>9){
					
					break;
				}
			}	
			tmpy--;	
		}
		if(turn == 3){
			while(!((mp.getBlock(tmpy,tmpx).stateG()==1||mp.getBlock(tmpy,tmpx).stateG()==2)
				||(mp.getBlock(tmpy,tmpx).stateG()==6||mp.getBlock(tmpy,tmpx).stateG()==7)
				||(mp.getBlock(tmpy,tmpx).stateG()==8||mp.getBlock(tmpy,tmpx).stateG()==9))){
				tmpx--;
				if(tmpx<0){
					
					break;
				}
			}		
			tmpx++;
		}
		x = (tmpx)*playerSize+leftBorder+playerSize;
		y = tmpy*playerSize + playerSize+upBorder;
		state = 4;	
	}
	if(skill == 2){
		skillTimer.start();
		undeadTimer.start();
	}
	if(skill == 3){
		skillTimer.start();
		killTimer.start();
	}
	if(skill == 4){
		skillTimer.start();
		x = anotherPlayer.xreturn();
		y = anotherPlayer.yreturn();
		turn = anotherPlayer.turnreturn();
		state = anotherPlayer.statereturn();
		
	}
	if(skill == 5){
		if((x>anotherPlayer.xreturn()&&y==anotherPlayer.yreturn()&&turn==3&&anotherPlayer.turnreturn()==1)
		||(x<anotherPlayer.xreturn()&&y==anotherPlayer.yreturn()&&turn==1&&anotherPlayer.turnreturn()==3)
		||(x==anotherPlayer.xreturn()&&y>anotherPlayer.yreturn()&&turn==0&&anotherPlayer.turnreturn()==2)
		||(x==anotherPlayer.xreturn()&&y<anotherPlayer.yreturn()&&turn==2&&anotherPlayer.turnreturn()==0)){
			skillTimer.start();
			int tmpx = x;
			x = anotherPlayer.xreturn();
			anotherPlayer.xassign(tmpx);
			int tmpy = y;
			y = anotherPlayer.yreturn();
			anotherPlayer.yassign(tmpy);
			int tmpturn = turn;
			turn = anotherPlayer.turnreturn();
			anotherPlayer.turnassign(tmpturn);
			int tmpstate = state;
			state = anotherPlayer.statereturn();
			anotherPlayer.stateassign(tmpstate);
		}
			
	}
	if(skill == 6){
		int tmpy = blockY,tmpx = blockX;
		bool caught = false;
		skillTimer.start();
		if(turn == 0){
			while(!((mp.getBlock(tmpy,tmpx).stateG()==1||mp.getBlock(tmpy,tmpx).stateG()==2)
				||(mp.getBlock(tmpy,tmpx).stateG()==6||mp.getBlock(tmpy,tmpx).stateG()==7)
				||(mp.getBlock(tmpy,tmpx).stateG()==8||mp.getBlock(tmpy,tmpx).stateG()==9))){
				if(x==anotherPlayer.xreturn() &&tmpy==(anotherPlayer.yreturn()-(upBorder +playerSize))/playerSize){
					caught = true;
					break;
				} 
				tmpy--;
				if(tmpy<0){
					break;
				}
			}
			tmpy++;
		}
		if(turn == 1){
			while(!((mp.getBlock(tmpy,tmpx).stateG()==1||mp.getBlock(tmpy,tmpx).stateG()==2)
				||(mp.getBlock(tmpy,tmpx).stateG()==6||mp.getBlock(tmpy,tmpx).stateG()==7)
				||(mp.getBlock(tmpy,tmpx).stateG()==8||mp.getBlock(tmpy,tmpx).stateG()==9))){
				if(tmpx==(anotherPlayer.xreturn()-(leftBorder +playerSize))/playerSize &&y==anotherPlayer.yreturn()){
					caught = true;
					break;
				} 
				tmpx++;
				if(tmpx>13){
					
					break;
				}
			}
			tmpx--;		
		}
		if(turn == 2){
			while(!((mp.getBlock(tmpy,tmpx).stateG()==1||mp.getBlock(tmpy,tmpx).stateG()==2)
				||(mp.getBlock(tmpy,tmpx).stateG()==6||mp.getBlock(tmpy,tmpx).stateG()==7)
				||(mp.getBlock(tmpy,tmpx).stateG()==8||mp.getBlock(tmpy,tmpx).stateG()==9))){
				if(x==anotherPlayer.xreturn() &&tmpy==(anotherPlayer.yreturn()-(upBorder +playerSize))/playerSize){
					caught = true;
					break;
				} 
				tmpy++;
				if(tmpy>9){
					
					break;
				}
			}	
			tmpy--;	
		}
		if(turn == 3){
			while(!((mp.getBlock(tmpy,tmpx).stateG()==1||mp.getBlock(tmpy,tmpx).stateG()==2)
				||(mp.getBlock(tmpy,tmpx).stateG()==6||mp.getBlock(tmpy,tmpx).stateG()==7)
				||(mp.getBlock(tmpy,tmpx).stateG()==8||mp.getBlock(tmpy,tmpx).stateG()==9))){
				if(tmpx==((anotherPlayer.xreturn()-(leftBorder +playerSize))/playerSize) &&y==anotherPlayer.yreturn()){
					caught = true;
					break;
				} 
				tmpx--;
				if(tmpx<0){
					
					break;
				}
			}		
			tmpx++;
		}
		if(caught){
			anotherPlayer.xassign(x);
			anotherPlayer.yassign(y);
			anotherPlayer.turnassign(turn);
			anotherPlayer.stateassign(state);
			anotherPlayer.speedPassign(50);
			caughtTimer.start();
		}
	}
}
/***********************************************************************/
void player2::skilldetect(map &mp,SDL_Renderer* gRenderer,player1 &anotherPlayer){
	if(undeadTimer.counter(undeadtime))undeadTimer.stop();
	if(killTimer.counter(killtime)){
		killTimer.stop();
		speedP = 1;
	}
	if(killTimer.isStarted()){
		speedP = 15;
		if(abs(anotherPlayer.xreturn()-x)<5&&abs(anotherPlayer.yreturn()-y)<5&&!killTimer.counter(killtime)){
			
			anotherPlayer.kill();
		}
	}
	if(caughtTimer.counter(caughttime)){
		anotherPlayer.speedPassign(1);
		caughtTimer.stop();
	}
	if(skillTimer.counter(cooltime))skillTimer.stop();
}

player2::player2(int Skill):player(Skill){
	x =  rightBorder -2*playerSize;
	y = downBorder -2*playerSize;
}

player2::~player2(){
}
void player2::pollEvents(SDL_Event &event,map &mp,raserSystem &rasSys,SDL_Renderer* gRenderer,player1 &anotherPlayer){
//	std::cout<<speed;
	if(event.type == SDL_KEYDOWN){
			int speed = Ospeed/speedP;
			if(speedTimer.isStarted())speed = 50;
			switch(event.key.keysym.sym){
			case SDLK_a:
					if(state==1||state==3||state==4){
						
						if(turn!=3){
							turn =3;
							playerState = turn + skill*4;
							loadStatus(gRenderer);	
						}
						else if(x-speed>=leftBorder+playerSize){
							if(blockX>0){
								if((mp.getBlock(blockY,blockX-1).stateG()==1||mp.getBlock(blockY,blockX-1).stateG()==2)
									||(mp.getBlock(blockY,blockX-1).stateG()==6||mp.getBlock(blockY,blockX-1).stateG()==7)
									||(mp.getBlock(blockY,blockX-1).stateG()==8||mp.getBlock(blockY,blockX-1).stateG()==9))
								
								{
//									std::cout<<mp.getBlock(blockY,blockX-1).stateGet();
								int tmp = std::min(x-(blockX)*playerSize-leftBorder-playerSize,speed);
								if(!tmp)x-=tmp;
//								x-=std::min(x-(blockX)*playerSize-leftBorder-playerSize,speed);
								
								}else{
									x-=speed;
								}
							}
//							x-=speed;
							state = 3;
						}
					}
					break;
			case SDLK_d:
				if(state==1||state==3||state==4){
					if(turn!=1){
						turn =1;
						playerState = turn + skill*4;
						loadStatus(gRenderer);		
					}
					else if(x+speed<=rightBorder-2*playerSize){
							if(blockX<13){
								
								if((x-leftBorder)%playerSize==0&&((mp.getBlock(blockY,blockX+1).stateG()==1||mp.getBlock(blockY,blockX+1).stateG()==2)
									||(mp.getBlock(blockY,blockX+1).stateG()==6||mp.getBlock(blockY,blockX+1).stateG()==7)
									||(mp.getBlock(blockY,blockX+1).stateG()==8||mp.getBlock(blockY,blockX+1).stateG()==9))){
//									std::cout<<mp.getBlock(blockY,blockX-1).stateGet();
									int tmp = std::min((blockX+1)*playerSize-leftBorder-playerSize-x,speed);
									if(!tmp)x+=tmp;	
//									std::cout<<"111\n";
								}else if((x-leftBorder)%playerSize!=0&&((mp.getBlock(blockY,blockX+2).stateG()==1||mp.getBlock(blockY,blockX+2).stateG()==2)
									||(mp.getBlock(blockY,blockX+2).stateG()==6||mp.getBlock(blockY,blockX+2).stateG()==7)
									||(mp.getBlock(blockY,blockX+2).stateG()==8||mp.getBlock(blockY,blockX+2).stateG()==9)))	{
									int tmp = std::min((blockX+1)*playerSize+leftBorder+playerSize-x,speed);
									if(!tmp)x+=tmp; 
//									std::cout<<tmp<<"222\n";
//									system("pause");
								
								}else{
									x+=speed;
								}
								
								
							}
						state = 1;
					}
				}	
				break;
			case SDLK_w:
				if(state==0||state==2||state==4){
					if(turn!=0){
						turn =0;
						playerState = turn + skill*4;
						loadStatus(gRenderer);		
					}
					else if(y-speed>=upBorder+playerSize){
							if(blockY){
								if((mp.getBlock(blockY-1,blockX).stateG()==1||mp.getBlock(blockY-1,blockX).stateG()==2)
									||(mp.getBlock(blockY-1,blockX).stateG()==6||mp.getBlock(blockY-1,blockX).stateG()==7)
									||(mp.getBlock(blockY-1,blockX).stateG()==8||mp.getBlock(blockY-1,blockX).stateG()==9)){
//									std::cout<<mp.getBlock(blockY,blockX-1).stateGet();
								int tmp = std::min(y-(blockY)*playerSize-upBorder-playerSize,speed);
								if(!tmp)y-=tmp;
//								x-=std::min(x-(blockX)*playerSize-leftBorder-playerSize,speed);
								
								}else{
									y-=speed;
								}
							}
						state = 0;
					}
				}
				break;
			case SDLK_s:
				if(state==0||state==2||state==4){
					if(turn!=2){
						turn =2;	
						playerState = turn + skill*4;
						loadStatus(gRenderer);	
					}
					else if(y+speed<=downBorder-2*playerSize){
						if(blockY<11){
							if((y-upBorder)%playerSize==0&&(mp.getBlock(blockY+1,blockX).stateG()==1||mp.getBlock(blockY+1,blockX).stateG()==2)
									||(mp.getBlock(blockY+1,blockX).stateG()==6||mp.getBlock(blockY+1,blockX).stateG()==7)
									||(mp.getBlock(blockY+1,blockX).stateG()==8||mp.getBlock(blockY+1,blockX).stateG()==9)){
//									std::cout<<mp.getBlock(blockY,blockX-1).stateGet();
								int tmp = std::min((blockY+1)*playerSize-leftBorder-playerSize-y,speed);
								if(!tmp)y+=tmp;	
//									std::cout<<"111\n";
								}else if((y-upBorder)%playerSize!=0&&((mp.getBlock(blockY+2,blockX).stateG()==1||mp.getBlock(blockY+2,blockX).stateG()==2)
									||(mp.getBlock(blockY+2,blockX).stateG()==6||mp.getBlock(blockY+2,blockX).stateG()==7)
									||(mp.getBlock(blockY+2,blockX).stateG()==8||mp.getBlock(blockY+2,blockX).stateG()==9)))	{
									int tmp = std::min((blockY+1)*playerSize+upBorder+playerSize-y,speed);
									if(!tmp)y+=tmp; 
//									std::cout<<tmp<<"222\n";
//									system("pause");
								
								}else{
									y+=speed;
								}
							}
						state = 2;
					}
					
				}
				break;
				
			case SDLK_LSHIFT:
				if(!itemPlaced && state == 4){
					itemPlaced = true;
					shootTimer.start();
					itemX = blockX;
					itemY = blockY;
					if(turn == 0){
						mp.getBlock(blockY,blockX).stateAssign(6);
						itemState = 6;
					}
					if(turn == 1){
						mp.getBlock(blockY,blockX).stateAssign(7);
						itemState = 7;
					}
					if(turn == 2){
						mp.getBlock(blockY,blockX).stateAssign(8);
						itemState = 8;
					}
					if(turn == 3){
						mp.getBlock(blockY,blockX).stateAssign(9);
						itemState = 9;
					}		
					mp.blockRendering(blockY,blockX,gRenderer);				
				}	else if(itemPlaced && shootTimer.counter(shottime)){
					if(itemState == 6&&itemY-1>-1)rasSys.playerShoot(itemY-1,itemX,itemState-6);
					if(itemState == 7&&itemX+1<14)rasSys.playerShoot(itemY,itemX+1,itemState-6);
					if(itemState == 8&&itemY+1<10)rasSys.playerShoot(itemY+1,itemX,itemState-6);
					if(itemState == 9&&itemX-1>-1)rasSys.playerShoot(itemY,itemX-1,itemState-6);

					mp.getBlock(itemY,itemX).stateAssign(0);
//					mp.blockRendering(itemY,itemX,gRenderer);
					itemY = -1;
					itemX = -1;
					itemState = 0;
					itemPlaced = false;
					shootTimer.stop();
				}
				break;
				
			case SDLK_LCTRL:
				if(state == 4){
					
					if((!itemP.isStarted())&&addItem.size()>0){
//						std::cout<<"enter\n";
						int tmp = addItem.front();
						itemP.start();
						addItem.pop();
						if(tmp == 11){
							speedTimer.start();
							bananaTime.stop();
							speedP = 1;
						}
						if(tmp == 12){
							mp.getBlock(blockY,blockX).stateAssign(15);
							bananaTime.start();
						}
						if(tmp==13){
							mp.getBlock(blockY,blockX).stateAssign(10);
							rasSys.playerItemPlaced(blockY,blockX);
							
						}
						if(tmp ==14){
							mp.getBlock(blockY,blockX).stateAssign(2);
						}
						
					}
					mp.blockRendering(blockY,blockX,gRenderer);				
				}
				break;
			 case SDLK_q:
			 	if((!skillTimer.isStarted())){
			 		std::cout<<"skill using";
			 		skillusing(mp,anotherPlayer);
//			 		if(crazy)++(*this);
				 }
			}
	}
		
		
}

void player::move(map &mp){
			
//			if(state==4) moveCnt=0;
//			else moveCnt++;
//			std::cout<<state<<" "<<moveCnt<<"\n";
			int tmpx = x-leftBorder-playerSize;
			int tmpy = y-upBorder - playerSize;
			int speed = Ospeed/speedP;
//			std::cout<<tmpx<<" ";
//			std::cout<<tmpy<<std::endl;
			
//			if(moveCnt==50){//fix rate
//				moveCnt = 0;
	
				if(state==0){
					if(tmpy%playerSize!=0){
						y-=std::min(y-(blockY)*playerSize-upBorder-playerSize,speed);
					}else state = 4;
				}
				if(state==1){
					if(tmpx%playerSize!=0){
						x+=std::min((blockX+1)*playerSize+leftBorder+playerSize-x,speed);
					}else state = 4;
				}
				if(state==2){
					if(tmpy%playerSize!=0){
						y+=std::min((blockY+1)*playerSize+upBorder+playerSize-y,speed);
					}else state = 4;
				}
				if(state==3){
					
					if(tmpx%playerSize!=0){
//						system("pause");
//						if(x>=leftBorder-playerSize){
							x-=std::min(x-(blockX)*playerSize-leftBorder-playerSize,speed);
//						}
					}else state = 4;
				}
//			}
			
			
		
}