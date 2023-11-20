#pragma once

#include <SDL.h>

class TitleScreen {
public:
    TitleScreen(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~TitleScreen();

    void handleEvents();
    void update();
    void render();

private:
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;
    int screenWidth, screenHeight;
};
