#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include"raser.h"
#include <stack>
#include <queue>


playerblock tmpblock;

std::stack <playerblock> raserChain;
std::queue <timerRaser> timerRaserChain;

raser::raser(map &mp){
	randomPick(mp);
}

bool operator!(const raserSystem& ras) {
    return ras.overTime;
}

void raserSystem::reset(){
	while(!raserChain.empty())raserChain.pop();
	while(!timerRaserChain.empty())timerRaserChain.pop();
	if(shootCountdown.isStarted()){
		shootCountdown.stop();
		for(int i=0;i<number;i++){
			delete raserPtr[i];
		}
		delete []raserPtr;
	}
	overTime = false;

}

void raser::randomPick(map &mp) {
    // Seed the random number generator with the current time
    
	
    // Generate a random number between 0 and 13
    do{
//	    int randomNumber = std::rand() % (14*100); 
//		int randomNumber = std::rand() % (14*100);// 14 ensures the range includes 0 to 13
		x = (std::rand()/100) % 14;
		y = std::rand()%10;
//		x = 4;
//		y = 4;
		stay = false;
		if(mp.getBlock(y,x).stateG()==2)stay = true;
	}while(mp.getBlock(y,x).stateG()==1);
//	std::cout <<y <<" "<<x<<"\n";
	
    // Print the random number

	state = 0;
    
}

void raser::preview(map &mp,SDL_Renderer* gRenderer ){
	if(mp.getBlock(y,x).stateG()==2||mp.getBlock(y,x).stateG()==16){
		mp.getBlock(y,x).stateAssign(16);
	}else{
		mp.getBlock(y,x).stateAssign(10);
	}
	
	mp.blockRendering(y,x,gRenderer);
}

void raser::raserShoot(map &mp){
	int tmp =0;
	std::pair<int, int> tmpP = {y, x};
	if(stay){
		mp.getBlock(y,x).itemDropping();
		return ;
	}
//	if(mp.getBlock(y,x).stateG()==2){
//		
//		return ;
//	}
	while(mp.getBlock(y,x+tmp).stateG()!=1){//left
		tmpP.second = x+tmp;
		linex.push_back(tmpP);
		if(mp.getBlock(y,x+tmp).stateG()==2){
			mp.getBlock(y,x+tmp).itemDropping();
			break;
		}
		if(mp.getBlock(y,x+tmp).stateG()==6){
			tmpblock = {x+tmp,y,0};
			raserChain.push(tmpblock);
			break;
		}
		if(mp.getBlock(y,x+tmp).stateG()==7){
			tmpblock = {x+tmp,y,0};
			raserChain.push(tmpblock);
			tmpblock = {x+tmp,y,1};
			raserChain.push(tmpblock);
			tmpblock = {x+tmp,y,2};
			raserChain.push(tmpblock);
			break;
		}
		if(mp.getBlock(y,x+tmp).stateG()==8){
			tmpblock = {x+tmp,y,2};
			raserChain.push(tmpblock);
			break;
		}
		if(mp.getBlock(y,x+tmp).stateG()==9){
			tmpblock = {x+tmp,y,0};
			raserChain.push(tmpblock);
			tmpblock = {x+tmp,y,2};
			raserChain.push(tmpblock);
			break;
		}		
		tmp++;
		if(x+tmp>13)break;
	}
	tmp =0;
	while(mp.getBlock(y,x-tmp).stateG()!=1){//right
		tmpP.second = x-tmp;
		linex.push_back(tmpP);
		if(mp.getBlock(y,x-tmp).stateG()==2){
			mp.getBlock(y,x-tmp).itemDropping();
			break;
		}
		if(mp.getBlock(y,x-tmp).stateG()==6){
			tmpblock = {x-tmp,y,0};
			raserChain.push(tmpblock);
			break;
		}
		if(mp.getBlock(y,x-tmp).stateG()==7){
			tmpblock = {x-tmp,y,0};
			raserChain.push(tmpblock);
			tmpblock = {x-tmp,y,2};
			raserChain.push(tmpblock);
			break;
		}
		if(mp.getBlock(y,x-tmp).stateG()==8){
			tmpblock = {x-tmp,y,2};
			raserChain.push(tmpblock);
			break;
		}
		if(mp.getBlock(y,x-tmp).stateG()==9){
			tmpblock = {x-tmp,y,0};
			raserChain.push(tmpblock);
			tmpblock = {x-tmp,y,2};
			raserChain.push(tmpblock);
			tmpblock = {x-tmp,y,3};
			raserChain.push(tmpblock);
			break;
		}	
		tmp++;
		if(x-tmp<0)break;
	}
	
//		for(int i=0;i<linex.size();i++){
//		std::cout<<linex[i].first<<" "<<linex[i].second<<std::endl;
//	}
//	std::cout<<"horizontal\n";
	
//	std::cout <<y <<" "<<x<<"\n";
	tmp = 0;
	tmpP = {y, x};
	while(mp.getBlock(y+tmp,x).stateG()!=1){//down
		tmpP.first = y+tmp;
		liney.push_back(tmpP);
		if(mp.getBlock(y+tmp,x).stateG()==2){
			mp.getBlock(y+tmp,x).itemDropping();
			break;
		}
		if(mp.getBlock(y+tmp,x).stateG()==6){

			tmpblock = {x,y+tmp,1};
			raserChain.push(tmpblock);
			tmpblock = {x,y+tmp,3};
			raserChain.push(tmpblock);
			break;
		}
		if(mp.getBlock(y+tmp,x).stateG()==7){
			tmpblock = {x,y+tmp,1};
			raserChain.push(tmpblock);
			break;
		}
		if(mp.getBlock(y+tmp,x).stateG()==8){
			tmpblock = {x,y+tmp,1};
			raserChain.push(tmpblock);
			tmpblock = {x,y+tmp,2};
			raserChain.push(tmpblock);
			tmpblock = {x,y+tmp,3};
			raserChain.push(tmpblock);
			break;
		}
		if(mp.getBlock(y+tmp,x).stateG()==9){
			tmpblock = {x,y+tmp,3};
			raserChain.push(tmpblock);
			break;
		}
		tmp++;
		if(y+tmp>9)break;
	}
	tmp =0;
	while(mp.getBlock(y-tmp,x).stateG()!=1){//up
		tmpP.first = y-tmp;
		liney.push_back(tmpP);
		if(mp.getBlock(y-tmp,x).stateG()==2){
			mp.getBlock(y-tmp,x).itemDropping();
			break;
		}
		if(mp.getBlock(y-tmp,x).stateG()==6){
			tmpblock = {x,y-tmp,0};
			raserChain.push(tmpblock);
			tmpblock = {x,y-tmp,1};
			raserChain.push(tmpblock);
			tmpblock = {x,y-tmp,3};
			raserChain.push(tmpblock);
			break;
		}
		if(mp.getBlock(y-tmp,x).stateG()==7){
			tmpblock = {x,y-tmp,1};
			raserChain.push(tmpblock);
			break;
		}
		if(mp.getBlock(y-tmp,x).stateG()==8){
			tmpblock = {x,y-tmp,1};
			raserChain.push(tmpblock);
			tmpblock = {x,y-tmp,3};
			raserChain.push(tmpblock);
			break;
		}
		if(mp.getBlock(y-tmp,x).stateG()==9){
			tmpblock = {x,y-tmp,3};
			raserChain.push(tmpblock);
			break;
		}
		tmp++;
		if(y-tmp<0)break;
	}

//	for(int i=0;i<liney.size();i++){
//		std::cout<<liney[i].first<<" "<<liney[i].second<<std::endl;
//	}
//	std::cout<<"vertiacl\n";
	
}

void raser::raserShowing(map &mp,SDL_Renderer* gRenderer){
	if(state == 0){
		for(int i=0;i<linex.size();i++){//3 vertical 4 horizontal 5 x  
			
			if(mp.getBlock(linex[i].first,linex[i].second).stateG()==3||mp.getBlock(linex[i].first,linex[i].second).stateG()==5){
				mp.getBlock(linex[i].first,linex[i].second).stateChange(5);
				mp.getBlock(linex[i].first,linex[i].second).xbroke();
				mp.getBlock(linex[i].first,linex[i].second).ybroke();
			}
			else{
				mp.getBlock(linex[i].first,linex[i].second).stateChange(4);
				mp.getBlock(linex[i].first,linex[i].second).ybroke();
			}
			mp.blockRendering(linex[i].first,linex[i].second,gRenderer);
			
		}
		for(int i=0;i<liney.size();i++){//3 vertical 4 horizontal 5 x
			
			if(mp.getBlock(liney[i].first,liney[i].second).stateG()==4||mp.getBlock(liney[i].first,liney[i].second).stateG()==5){
				mp.getBlock(liney[i].first,liney[i].second).stateChange(5);
				mp.getBlock(liney[i].first,liney[i].second).xbroke();
				mp.getBlock(liney[i].first,liney[i].second).ybroke();
			}else{
				mp.getBlock(liney[i].first,liney[i].second).stateChange(3);
				mp.getBlock(liney[i].first,liney[i].second).xbroke();
			}
			mp.blockRendering(liney[i].first,liney[i].second,gRenderer);
		}
		mp.getBlock(y,x).stateChange(5);
		mp.getBlock(y,x).xbroke();
		mp.getBlock(y,x).ybroke();
		mp.blockRendering(y,x,gRenderer);
	}
//	if(state == 1){
//		for(int i=0;i<linex.size();i++){//3 vertical 4 horizontal 5 x
//			mp.getBlock(linex[i].first,linex[i].second).stateChange(0);
//			mp.blockRendering(linex[i].first,linex[i].second,gRenderer);	
//		}
//		for(int i=0;i<liney.size();i++){//3 vertical 4 horizontal 5 x
//			mp.getBlock(linex[i].first,linex[i].second).stateChange(0);
//			mp.blockRendering(linex[i].first,linex[i].second,gRenderer);
//		}
//		linex.clear();
//		liney.clear();
//		raserShoot(mp);
//		state = 2;
//	}
}

raser::~raser(){
	linex.clear();
	liney.clear();

//	std::cout<<"okay\n";
}


raserSystem::raserSystem(uint32_t  I){
	interval = I;
}
raserSystem::~raserSystem(){
	if(shootCountdown.isStarted()){
		shootCountdown.stop();
		for(int i=0;i<number;i++){
			delete raserPtr[i];
		}
		delete []raserPtr;
	}
}
void raserSystem::intervalSet(uint32_t  I){
	interval = I;
}

void raserSystem::raserinit(map &mp){
	if(!shootCountdown.isStarted()){
//		std::cout<<"systeminit\n";
		raserPtr = new raser*[number];
		for(int i=0;i<number;i++){
			raserPtr[i] = new raser(mp);
		}
		shootCountdown.start();
		if(overTime){
			interval -=500;
			if(interval<1000)interval = 1000;
		}
		std::cout<<interval<<std::endl;
	}
}

void raserSystem::numberChange(int N){
	
	if(!shootCountdown.isStarted()){
		number  = N;
	}
}

void raserSystem::overtime(){
	overTime = true;
}

void raserSystem::raserShoot(map &mp,SDL_Renderer* gRenderer){
	
	if(shootCountdown.counter(interval)){
//		std::cout<<"systemshoot\n";
		for(int i=0;i<number;i++){
			raserPtr[i][0].raserShoot(mp);
			raserPtr[i][0].raserShowing(mp,gRenderer);
		}
		
		shootCountdown.stop();
		for(int i=0;i<number;i++){
			delete raserPtr[i];
		}
		delete []raserPtr;
//		raserPtr[0][0].raserShoot(mp);
//		std::cout<<;
	}else{
		for(int i=0;i<number;i++){
			
			raserPtr[i][0].preview(mp,gRenderer);
		}
	}
}

void raserSystem::chainCheck(map &mp,SDL_Renderer* gRenderer){
//	if(raserChain.size()>0)std::cout<<raserChain.size()<<std::endl;
	timeLineRaser();
	while(raserChain.size()>0){
//		system("pause");
		playerblock tmpBlock = raserChain.top();
		std::cout<<raserChain.top().x<<" "<<raserChain.top().y<<" "<<raserChain.top().shoot<<std::endl;
		raserChain.pop();
		int y = tmpBlock.y, x = tmpBlock.x;
		if(mp.getBlock(y,x).stateG()==2){
			mp.getBlock(y,x).stateChange(5);
			mp.blockRendering(y,x,gRenderer);
			return;
		}
		mp.getBlock(y,x).stateChange(5);
		mp.blockRendering(y,x,gRenderer);
//		std::cout<<tmpBlock.shoot<<std::endl;
		if(tmpBlock.shoot == 0){
			int tmp = 0;
			while(mp.getBlock(y-tmp,x).stateG()!=1){//up
			
			if(mp.getBlock(y-tmp,x).stateG()==4||mp.getBlock(y-tmp,x).stateG()==5){
				mp.getBlock(y-tmp,x).stateChange(5);
				mp.getBlock(y-tmp,x).xbroke();
				mp.getBlock(y-tmp,x).ybroke();
				mp.blockRendering(y-tmp,x,gRenderer);
			}
			else if(mp.getBlock(y-tmp,x).stateG()==2){
				mp.getBlock(y-tmp,x).stateChange(3);
				mp.getBlock(y-tmp,x).ybroke();
				mp.blockRendering(y-tmp,x,gRenderer);
				mp.getBlock(y-tmp,x).itemDropping();
				break;
			}else if(mp.getBlock(y-tmp,x).stateG()==0){
				mp.getBlock(y-tmp,x).stateChange(3);
				mp.getBlock(y-tmp,x).ybroke();
				mp.blockRendering(y-tmp,x,gRenderer);
			}
			
				if(mp.getBlock(y-tmp,x).stateG()==6){
					tmpblock = {x,y-tmp,0};
					raserChain.push(tmpblock);
					tmpblock = {x,y-tmp,1};
					raserChain.push(tmpblock);
					tmpblock = {x,y-tmp,3};
					raserChain.push(tmpblock);
					break;
				}
				if(mp.getBlock(y-tmp,x).stateG()==7){
					tmpblock = {x,y-tmp,1};
					raserChain.push(tmpblock);
					break;
				}
				if(mp.getBlock(y-tmp,x).stateG()==8){
					tmpblock = {x,y-tmp,1};
					raserChain.push(tmpblock);
					tmpblock = {x,y-tmp,3};
					raserChain.push(tmpblock);
					break;
				}
				if(mp.getBlock(y-tmp,x).stateG()==9){
					tmpblock = {x,y-tmp,3};
					raserChain.push(tmpblock);
					break;
				}
				tmp++;
				if(y-tmp<0)break;
			}
			
			
		}
		if(tmpBlock.shoot == 1){
			int tmp = 0;
			while(mp.getBlock(y,x+tmp).stateG()!=1){//right
			
			if(mp.getBlock(y,x+tmp).stateG()==3||mp.getBlock(y,x+tmp).stateG()==5){
				mp.getBlock(y,x+tmp).stateChange(5);
				mp.getBlock(y,x+tmp).xbroke();
				mp.getBlock(y,x+tmp).ybroke();
				mp.blockRendering(y,x+tmp,gRenderer);
			}
			else if(mp.getBlock(y,x+tmp).stateG()==2){
				mp.getBlock(y,x+tmp).stateChange(4);
				mp.getBlock(y,x+tmp).xbroke();
				mp.blockRendering(y,x+tmp,gRenderer);
				mp.getBlock(y,x+tmp).itemDropping();
				break;
			}else if(mp.getBlock(y,x+tmp).stateG()==0){
				mp.getBlock(y,x+tmp).stateChange(4);
				mp.getBlock(y,x+tmp).xbroke();
				mp.blockRendering(y,x+tmp,gRenderer);
			}

					if(mp.getBlock(y,x+tmp).stateG()==6){
//						std::cout<<"yes";
						tmpblock = {x+tmp,y,0};
						raserChain.push(tmpblock);
						break;
					}
					if(mp.getBlock(y,x+tmp).stateG()==7){
						tmpblock = {x+tmp,y,0};
						raserChain.push(tmpblock);
						tmpblock = {x+tmp,y,1};
						raserChain.push(tmpblock);
						tmpblock = {x+tmp,y,2};
						raserChain.push(tmpblock);
						break;
					}
					if(mp.getBlock(y,x+tmp).stateG()==8){
						tmpblock = {x+tmp,y,2};
						raserChain.push(tmpblock);
						break;
					}
					if(mp.getBlock(y,x+tmp).stateG()==9){
						tmpblock = {x+tmp,y,0};
						raserChain.push(tmpblock);
						tmpblock = {x+tmp,y,2};
						raserChain.push(tmpblock);
						
						break;
					}		
					tmp++;
					if(x+tmp>13)break;
			}
			
			
		}
		if(tmpBlock.shoot == 2){
			int tmp = 0;
			while(mp.getBlock(y+tmp,x).stateG()!=1){//down
			
			if(mp.getBlock(y+tmp,x).stateG()==4||mp.getBlock(y+tmp,x).stateG()==5){
				mp.getBlock(y+tmp,x).stateChange(5);
				mp.getBlock(y+tmp,x).xbroke();
				mp.getBlock(y+tmp,x).ybroke();
				mp.blockRendering(y+tmp,x,gRenderer);
			}
			else if(mp.getBlock(y+tmp,x).stateG()==2){
				mp.getBlock(y+tmp,x).stateChange(3);
				mp.getBlock(y+tmp,x).ybroke();
				mp.blockRendering(y+tmp,x,gRenderer);
				mp.getBlock(y+tmp,x).itemDropping();
				break;
			}else if(mp.getBlock(y+tmp,x).stateG()==0){
				mp.getBlock(y+tmp,x).stateChange(3);
				mp.getBlock(y+tmp,x).ybroke();
				mp.blockRendering(y+tmp,x,gRenderer);
			}

					if(mp.getBlock(y+tmp,x).stateG()==6){
						tmpblock = {x,y+tmp,1};
						raserChain.push(tmpblock);
						tmpblock = {x,y+tmp,3};
						raserChain.push(tmpblock);
						break;
					}
					if(mp.getBlock(y+tmp,x).stateG()==7){
						tmpblock = {x,y+tmp,1};
						raserChain.push(tmpblock);
						break;
					}
					if(mp.getBlock(y+tmp,x).stateG()==8){
						tmpblock = {x,y+tmp,1};
						raserChain.push(tmpblock);
						tmpblock = {x,y+tmp,2};
						raserChain.push(tmpblock);
						tmpblock = {x,y+tmp,3};
						raserChain.push(tmpblock);
						break;
					}
					if(mp.getBlock(y+tmp,x).stateG()==9){
						tmpblock = {x,y+tmp,3};
						raserChain.push(tmpblock);
						break;
					}
					tmp++;
					if(y+tmp>9)break;
			}
			
			
		}
		if(tmpBlock.shoot == 3){
			int tmp = 0;
			while(mp.getBlock(y,x-tmp).stateG()!=1){//left
			
			if(mp.getBlock(y,x-tmp).stateG()==3||mp.getBlock(y,x-tmp).stateG()==5){
				mp.getBlock(y,x-tmp).stateChange(5);
				mp.getBlock(y,x-tmp).xbroke();
				mp.getBlock(y,x-tmp).ybroke();
				mp.blockRendering(y,x-tmp,gRenderer);
			}
			else if(mp.getBlock(y,x-tmp).stateG()==2){
				mp.getBlock(y,x-tmp).stateChange(4);
				mp.getBlock(y,x-tmp).ybroke();
				mp.blockRendering(y,x-tmp,gRenderer);
				mp.getBlock(y,x-tmp).itemDropping();
				break;
			}else if(mp.getBlock(y,x-tmp).stateG()==0){
				mp.getBlock(y,x-tmp).stateChange(4);
				mp.getBlock(y,x-tmp).ybroke();
				mp.blockRendering(y,x-tmp,gRenderer);
			}

				if(mp.getBlock(y,x-tmp).stateG()==6){
					tmpblock = {x-tmp,y,0};
					raserChain.push(tmpblock);
					break;
				}
				if(mp.getBlock(y,x-tmp).stateG()==7){
					tmpblock = {x-tmp,y,0};
					raserChain.push(tmpblock);
					tmpblock = {x-tmp,y,2};
					raserChain.push(tmpblock);
					break;
				}
				if(mp.getBlock(y,x-tmp).stateG()==8){
					tmpblock = {x-tmp,y,2};
					raserChain.push(tmpblock);
					break;
				}
				if(mp.getBlock(y,x-tmp).stateG()==9){
					tmpblock = {x-tmp,y,0};
					raserChain.push(tmpblock);
					tmpblock = {x-tmp,y,2};
					raserChain.push(tmpblock);
					tmpblock = {x-tmp,y,3};
					raserChain.push(tmpblock);
					break;
				}	
				tmp++;
				if(x-tmp<0)break;
			}
			
			
		}
		
		
		mp.getBlock(y,x).stateChange(5);
		mp.getBlock(y,x).xbroke();
		mp.getBlock(y,x).ybroke();
		
		
		
		
		
	}


	
}

void raserSystem::timeLineRaser(){
	if(timerRaserChain.size()>0){
		if(timerRaserChain.front().counter(interval)){
			tmpblock = timerRaserChain.front().playerBlockReturn();
			raserChain.push(tmpblock);
			timerRaserChain.pop();
		}
	}
}

void raserSystem::playerItemPlaced(int y,int x){
	
	for(int i=0;i<4;i++){
		timerRaser tmp(y,x,i);
		timerRaserChain.push(tmp);
	}
}
void raserSystem::playerShoot(int y,int x,int turn){
	tmpblock = {x,y,turn};
	raserChain.push(tmpblock);
}


timerRaser::timerRaser(int y, int x,int shoot){
	control.x = x;
	control.y = y;
	control.shoot = shoot;
	start();
}
playerblock timerRaser::playerBlockReturn(){
	return control;
}
	

