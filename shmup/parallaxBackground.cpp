#include "parallaxBackground.h"
#include <iostream>

ParallaxBackground::ParallaxBackground(SDL_Renderer* renderer, const std::vector<std::string>& imagePaths, int scrollSpeed) {
    this->renderer = renderer;

    for (const auto& imagePath : imagePaths) {
        Layer layer;
        layer.texture = loadTexture(imagePath);
        layer.scrollSpeed = scrollSpeed;
        layer.yOffset = 0;
        layers.push_back(layer);
    }
}

ParallaxBackground::~ParallaxBackground() {
    for (const auto& layer : layers) {
        SDL_DestroyTexture(layer.texture);
    }
}

SDL_Texture* ParallaxBackground::loadTexture(const std::string& imagePath) {
    SDL_Surface* surface = SDL_LoadBMP(imagePath.c_str());
    if (!surface) {
        std::cerr << "Error loading image: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "Error creating texture: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    return texture;
}

void ParallaxBackground::render() {
    for (const auto& layer : layers) {
        SDL_Rect destRect = { 0, testYOffset, 640, 480 }; //RJP - this is hardcoded but shouldn't be.
        SDL_RenderCopy(renderer, layer.texture, nullptr, &destRect);
    }
}

void ParallaxBackground::scroll(int yOffset) {
    for (auto& layer : layers) {
        testYOffset += yOffset;
        if (layer.yOffset > screenHeight) {
            layer.yOffset -= screenHeight; // Wrap around if the layer goes off-screen
        }
    }
}