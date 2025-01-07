#pragma once

#include <SDL.h>
#include<iostream>

class LTexture
{
    public:
        //Initializes variables
        LTexture();
		LTexture(const LTexture& other);
        //Deallocates memory
        ~LTexture();

        //Loads image at specified path
        bool loadFromFile( SDL_Renderer* gRenderer ,std::string path );

        //Deallocates texture
        void free();
        
        void renderOrigin( int x, int y,SDL_Renderer* gRenderer, SDL_Rect* clip = NULL );
        void render(int x,int y,int w, int h,SDL_Renderer* gRenderer,SDL_Rect* clip = NULL );
		int getWidth();      
		int getHeight();
		SDL_Texture* getTexture();
    private:
        //The actual hardware texture
        SDL_Texture* mTexture;

        //Image dimensions
        int mWidth;
        int mHeight;
};



