#include "timer.h"
#include <string>
#include <sstream>
#include <iostream>
LTimer::LTimer(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, int x, int y, int w, int h)
    : renderer(renderer), font(font), textColor(color), isPaused(false), isStarted(false), texture(nullptr) {
    renderRect = {x, y, w, h};
}

LTimer::~LTimer() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void LTimer::start(int seconds) {
    totalTicks = seconds * 1000;  // Convert seconds to milliseconds
    startTicks = SDL_GetTicks();
    isPaused = false;
    isStarted = true;
    pausedTicks = 0;

    updateTexture();  // Initialize the text texture
}

void LTimer::stop() {
    isStarted = false;
    isPaused = false;
    startTicks = 0;
    pausedTicks = 0;
    totalTicks = 0;

    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void LTimer::pause() {
    if (isStarted && !isPaused) {
        isPaused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void LTimer::resume() {
    if (isStarted && isPaused) {
        isPaused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

int LTimer::getRemainingTime() {
    if (!isStarted) {
        return 0;
    }

    Uint32 elapsedTicks = isPaused ? pausedTicks : (SDL_GetTicks() - startTicks);
    int remainingTicks = static_cast<int>(totalTicks - elapsedTicks);
    int remainingSeconds = remainingTicks > 0 ? remainingTicks / 1000 : 0;
	//printf("Remaining Time: %d seconds\n", remainingSeconds); // Debug print
    return remainingSeconds; // Convert to seconds
}

bool LTimer::hasExpired()  {
    return getRemainingTime() <= 0;
}

//turn time into string format and then to texture
void LTimer::updateTexture() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    int remainingTime = getRemainingTime();
    int minutes = remainingTime / 60;
    int seconds = remainingTime % 60;

    std::stringstream timeStream;
    timeStream << minutes << ":" << (seconds < 10 ? "0" : "") << seconds;
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, timeStream.str().c_str(), textColor);
    if (!textSurface) {
    	std::cout << "TTF_RenderText_Solid Error: " << TTF_GetError() << std::endl;
	}
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
}

//字是以texture的方式上去 
void LTimer::render() {
    if (isStarted) {
        updateTexture();  // Update the texture with the latest time
        
        SDL_RenderCopy(renderer, texture, NULL, &renderRect);
    }
}
bool LTimer::isRunning() const {
    return isStarted;
}

int LTimer::getBeginTime() {
	return static_cast<int>(totalTicks);
}


RTimer::RTimer()
{
    //Initialize the variables
    mStartTicks = 0;
    mPausedTicks = 0;

    mPaused = false;
    mStarted = false;
}

void RTimer::start()
{
    //Start the timer
    mStarted = true;

    //Unpause the timer
    mPaused = false;

    //Get the current clock time
    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void RTimer::stop()
{
    //Stop the timer
    mStarted = false;

    //Unpause the timer
    mPaused = false;

    //Clear tick variables
    mStartTicks = 0;
    mPausedTicks = 0;
}

void RTimer::pause()
{
    //If the timer is running and isn't already paused
    if( mStarted && !mPaused )
    {
        //Pause the timer
        mPaused = true;

        //Calculate the paused ticks
        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}


void RTimer::unpause()
{
    //If the timer is running and paused
    if( mStarted && mPaused )
    {
        //Unpause the timer
        mPaused = false;

        //Reset the starting ticks
        mStartTicks = SDL_GetTicks() - mPausedTicks;

        //Reset the paused ticks
        mPausedTicks = 0;
    }
}

Uint32 RTimer::getTicks()
{
    //The actual timer time
    Uint32 time = 0;

    //If the timer is running
    if( mStarted )
    {
        //If the timer is paused
        if( mPaused )
        {
            //Return the number of ticks when the timer was paused
            time = mPausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicks() - mStartTicks;
        }
    }

    return time;
}

bool RTimer::isStarted()
{
    //Timer is running and paused or unpaused
    return mStarted;
}

bool RTimer::isPaused()
{
    //Timer is running and paused
    return mPaused && mStarted;
}

bool RTimer::counter(uint32_t T)
{
    //Timer is running and paused
     return (getTicks()>=T);
   
}

