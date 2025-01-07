#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include <vector>
#include "texture.h" 
class MusicPlayer {
public:
    MusicPlayer();
    ~MusicPlayer();
    bool loadMusic(const std::string& filePath);
    bool playMusic(int loops = -1);
    void pauseMusic();
    void resumeMusic();
    void stopMusic();
    void setMusicVolume(int volume);
	MusicPlayer& operator++();
	MusicPlayer& operator--();
	
    bool loadSoundEffect(const std::string& filePath);
    bool playSoundEffect(size_t index);

private:
    bool initialized = false;
    Mix_Music* bgMusic = nullptr;
    int volume;
    std::vector<Mix_Chunk*> soundEffects;
};

class Volume {
	private:
	    LTexture icons[4];        // Array of four textures for volume levels
	    int currentLevel;         // Current volume level (0-3)
	    SDL_Renderer* renderer;   // Renderer for rendering the volume icon
	    SDL_Rect renderRect;      // Rectangle for rendering the icon
	
	public:
	    Volume(SDL_Renderer* renderer, int x, int y, int w, int h);
	
	    void loadIcons(const std::string& path0, const std::string& path1,
	                   const std::string& path2, const std::string& path3);
	    void increaseVolume();
	    void decreaseVolume();
	    void renderVolume();
};
