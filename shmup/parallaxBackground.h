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

    void render();
    void scroll(int yOffset);

private:
    struct Layer {
        SDL_Texture* texture;
        int scrollSpeed;
        int yOffset;
    };

    SDL_Renderer* renderer;
    std::vector<Layer> layers;

    SDL_Texture* loadTexture(const std::string& imagePath);

    const int screenHeight = 480;

    int testYOffset = 0;
};

#endif // PARALLAX_BACKGROUND_H
