#include "parallaxBackground.h"

ParallaxBackground::ParallaxBackground(SDL_Renderer* renderer, const std::string& layer1Path, const std::string& layer2Path, int screenWidth, int screenHeight)
    : renderer(renderer), screenWidth(screenWidth), screenHeight(screenHeight) {
    backgroundLayer1 = IMG_LoadTexture(renderer, layer1Path.c_str());
    backgroundLayer2 = IMG_LoadTexture(renderer, layer2Path.c_str());
}

ParallaxBackground::~ParallaxBackground() {
    SDL_DestroyTexture(backgroundLayer1);
    SDL_DestroyTexture(backgroundLayer2);
}

void ParallaxBackground::Update() {
    // Update background layer positions vertically
    layer1Y += layer1VelY;
    layer2Y += layer2VelY;

    // Reset the layers when they go off the screen
    if (layer1Y >= screenHeight) {
        layer1Y = -screenHeight;
    }
    if (layer2Y >= screenHeight) {
        layer2Y = -screenHeight;
    }
}

void ParallaxBackground::Render() {
    // Render background layers
    SDL_Rect layer1Rect = { layer1Y, 0, screenWidth, screenHeight };
    SDL_Rect layer2Rect = { layer2Y, 0, screenWidth, screenHeight };

    SDL_RenderCopy(renderer, backgroundLayer1, NULL, &layer1Rect);
    SDL_RenderCopy(renderer, backgroundLayer2, NULL, &layer2Rect);
}

