#include "MusicPlayer.h"
MusicPlayer::MusicPlayer() {
    // Initialize SDL_Mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Failed to initialize SDL_Mixer: " << Mix_GetError() << std::endl;
        initialized = false;
    } else {
        initialized = true;
    }
}

MusicPlayer::~MusicPlayer() {
    // Free any loaded music or sound effects
    if (bgMusic) {
        Mix_FreeMusic(bgMusic);
    }
    for (auto& effect : soundEffects) {
        Mix_FreeChunk(effect);
    }

    // Close SDL_Mixer
    Mix_CloseAudio();
}
//Load music
bool MusicPlayer::loadMusic(const std::string& filePath) {
	if (!initialized) return false;

    bgMusic = Mix_LoadMUS(filePath.c_str());
    if (!bgMusic) {
        std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

//play music
bool MusicPlayer::playMusic(int loops) {
    if (!bgMusic) {
        std::cerr << "No music loaded to play." << std::endl;
        return false;
    }
    if (Mix_PlayMusic(bgMusic, loops) == -1) {
        std::cerr << "Failed to play music: " << Mix_GetError() << std::endl;
        return false;
    }
    volume = 96;
    setMusicVolume(volume);
    return true;
}


//pause music
void MusicPlayer::pauseMusic() {
    if (Mix_PlayingMusic()) {
        Mix_PauseMusic();
    }
}

//resume music
void MusicPlayer::resumeMusic() {
    if (Mix_PausedMusic()) {
        Mix_ResumeMusic();
    }
}

//stop music
void MusicPlayer::stopMusic() {
    Mix_HaltMusic();
}

//set music volume
void MusicPlayer::setMusicVolume(int volume) {
    Mix_VolumeMusic(this->volume);
}

// Operator overloading for volume control
MusicPlayer& MusicPlayer::operator++() {
    if (volume <128) volume += 32;
	setMusicVolume(volume);    
    std::cout << "Volume set to: " << volume << std::endl;
    return *this;
}

MusicPlayer& MusicPlayer::operator--() {
    if (volume > 0)	volume -= 32;
	setMusicVolume(volume);
    std::cout << "Volume set to: " << volume << std::endl;
    return *this;
}

//load sound effect
bool MusicPlayer::loadSoundEffect(const std::string& filePath) {
    if (!initialized) return false;

    Mix_Chunk* effect = Mix_LoadWAV(filePath.c_str());
    if (!effect) {
        std::cerr << "Failed to load sound effect: " << Mix_GetError() << std::endl;
        return false;
    }
    soundEffects.push_back(effect);
    return true;
}

//play sound effect
bool MusicPlayer::playSoundEffect(size_t index) {
    if (index >= soundEffects.size()) {
        std::cerr << "Invalid sound effect index." << std::endl;
        return false;
    }
    if (Mix_PlayChannel(-1, soundEffects[index], 0) == -1) {
        std::cerr << "Failed to play sound effect: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

//struct Volume
Volume::Volume(SDL_Renderer* renderer, int x, int y, int w, int h)
    : currentLevel(2), renderer(renderer) {
    renderRect = {x, y, w, h};
}

void Volume::loadIcons(const std::string& path0, const std::string& path1,
                       const std::string& path2, const std::string& path3) {
    if (!icons[0].loadFromFile(renderer, path0)) {
        printf("Failed to load volume icon 0!\n");
    }
    if (!icons[1].loadFromFile(renderer, path1)) {
        printf("Failed to load volume icon 1!\n");
    }
    if (!icons[2].loadFromFile(renderer, path2)) {
        printf("Failed to load volume icon 2!\n");
    }
    if (!icons[3].loadFromFile(renderer, path3)) {
        printf("Failed to load volume icon 3!\n");
    }
}

void Volume::increaseVolume() {
    if (currentLevel < 3) {
        currentLevel += 1;
        printf("Volume increased to level %d\n", currentLevel);
    } else {
        printf("Volume is already at maximum level.\n");
    }
}

void Volume::decreaseVolume() {
    if (currentLevel > 0) {
        currentLevel -= 1;
        printf("Volume decreased to level %d\n", currentLevel);
    } else {
        printf("Volume is already at minimum level.\n");
    }
}

void Volume::renderVolume() {
    if (currentLevel >= 0 && currentLevel < 4) {
        //printf("Rendering volume icon at level: %d\n", currentLevel);
        icons[currentLevel].renderOrigin(renderRect.x, renderRect.y, renderer); //
    } else {
        printf("Invalid volume level: %d\n", currentLevel);
    }
}
