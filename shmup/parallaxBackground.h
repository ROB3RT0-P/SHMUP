#ifndef PARALLAX_BACKGROUND_H
#define PARALLAX_BACKGROUND_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>

class ParallaxBackground {
public:
    ParallaxBackground(SDL_Renderer* renderer, const std::vector<std::string>& imagePaths, int scrollSpeed);
    ~ParallaxBackground();

    void scroll(int scrollSpeed);
    void randMovement(int speed);
    void titleRender();
    void render();

private:
    SDL_Renderer* renderer;
    std::vector<SDL_Texture*> layers;
    int scrollSpeed;
    int totalHeight;
    int yOffset;

    int screenHeight = 480;
};
#endif // PARALLAX_BACKGROUND_H