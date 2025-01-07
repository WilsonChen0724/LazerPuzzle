#include <iostream>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include"Window.h"

SDL_Renderer *Window::renderer = nullptr;

Window::Window(const std::string &title, int width, int height):
	_title (title), _width(width),_height(height)
{

		_closed = !init();
}

Window::~Window(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(_window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Window::init(){
	if(SDL_Init(SDL_INIT_VIDEO)!=0){
		std::cerr << "Failed to initailized SDL.\n";
		return 0;
	}
	
	if(IMG_Init(IMG_INIT_JPG)!=IMG_INIT_JPG){
		std::cerr<<"Failed to intialize SDL_image.\n";
		return false;
	}
	
	if(TTF_Init() == -1){
		std::cerr<<"Failed to intialize SDL_ttf.\n";
		return false;
	}
	
	
	_window = SDL_CreateWindow(
		_title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_width,_height,0
		
	);
	if(_window == nullptr){
		std::cerr<<"Failed to create window.\n";
		return 0;
	}
	renderer = SDL_CreateRenderer(_window ,-1, SDL_RENDERER_PRESENTVSYNC);
	
	if(renderer == nullptr){
		std::cerr << "Failed to create renderer.\n";
	}
	
	
	return true;
}

void Window::pollEvents(SDL_Event &event){
	switch(event.type){
			case SDL_QUIT:
				_closed = true;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE:
						_closed = true;
						break;
				}
				
			case SDL_MOUSEMOTION:
				std::cout<< event.motion.x <<", "<< event.motion.y<<'\n';
				break;
			case SDL_MOUSEBUTTONUP:
				std::cout<<"You release your mouse.\n";
				break;
				
			default:
				break;
		}
}

void Window::clear() const{
	/*SDL_SetRenderDrawColor(_renderer,0,0,200,255);
	SDL_RenderClear(_renderer);
	
	SDL_Rect rect;
	
	rect.w = 120;
	rect.h = 120;
	rect.x = (_width/2) - (rect.w/2);
	rect.y = (_height/2) - (rect.h/2);
	SDL_SetRenderDrawColor(_renderer, 200, 0, 200, 255);
	SDL_RenderFillRect(_renderer, &rect); */
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer,0,0,200,255);
	SDL_RenderClear(renderer);
	
	
}