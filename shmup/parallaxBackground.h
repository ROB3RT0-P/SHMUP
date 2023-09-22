#pragma once

#ifndef PARALLAX_BACKGROUND_H
#define PARALLAX_BACKGROUND_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class ParallaxBackground {
public:
    ParallaxBackground(SDL_Renderer* renderer, const std::string& layer1Path, const std::string& layer2Path, int screenWidth, int screenHeight);
    ~ParallaxBackground();

    void Update();
    void Render();

private:
    SDL_Renderer* renderer;
    SDL_Texture* backgroundLayer1;
    SDL_Texture* backgroundLayer2;
    int screenWidth;
    int screenHeight;
    int layer1Y;
    int layer2Y;
    int layer1VelY;
    int layer2VelY;
};

#endif // PARALLAX_BACKGROUND_H
