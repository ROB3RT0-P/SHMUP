/*******************************************
    Written by Robert Parry [RJP] - 2023
*******************************************/

#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

class AudioPlayer {
public:
    AudioPlayer();
    ~AudioPlayer();

    void play(const char* filePath);
    void pause();
    void resume();
    void stop();

private:
    Mix_Music* music;
};