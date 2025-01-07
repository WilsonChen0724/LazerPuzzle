#pragma once 
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class LTimer {
private:
    Uint32 startTicks;       // Start time in milliseconds
    Uint32 pausedTicks;      // Paused time in milliseconds
    Uint32 totalTicks;       // Total countdown time in milliseconds
    bool isPaused;           // Timer pause state
    bool isStarted;          // Timer start state

    SDL_Renderer* renderer;  // SDL renderer for rendering text
    TTF_Font* font;          // Font for rendering the timer text
    SDL_Color textColor;     // Text color for rendering
    SDL_Texture* texture;    // Texture for the rendered text
    SDL_Rect renderRect;     // Rectangle for rendering the timer text

    void updateTexture();    // Updates the text texture with the remaining time

public:
    LTimer(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, int x, int y, int w, int h);
    ~LTimer();

    void start(int seconds);       // Start the timer
    void stop();                   // Stop the timer
    void pause();                  // Pause the timer
    void resume();                 // Resume the timer
    int getRemainingTime() ;  // Get the remaining time in seconds
    bool hasExpired() ;       // Check if the timer has expired
    void render();                 // Render the timer text
    bool isRunning() const;
    int getBeginTime();
};



class RTimer
{
    public:
        //Initializes variables
        RTimer();

        //The various clock actions
        void start();
        void stop();
        void pause();
        void unpause();

        //Gets the timer's time
        uint32_t getTicks();

        //Checks the status of the timer
        bool isStarted();
        bool isPaused();
        bool counter(uint32_t T);

    private:
        //The clock time when the timer started
        uint32_t mStartTicks;

        //The ticks stored when the timer was paused
        uint32_t mPausedTicks;

        //The timer status
        bool mPaused;
        bool mStarted;
};

