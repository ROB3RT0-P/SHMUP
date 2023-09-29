#include "parallaxBackground.h"

#include <iostream>

ParallaxBackground::ParallaxBackground(SDL_Renderer* renderer, const std::vector<std::string>& imagePaths, int scrollSpeed)
    : renderer(renderer), screenHeight(0), yOffset(0) {

    for (const auto& path : imagePaths) {
        SDL_Surface* surface = IMG_Load(path.c_str());
        if (surface == nullptr) {
            SDL_Log("Failed to load image: %s", SDL_GetError());
            continue;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        if (texture == nullptr) {
            SDL_Log("Failed to create texture: %s", SDL_GetError());
            continue;
        }

        layers.push_back(texture);
        int w, h;
        SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
        totalHeight += h;
    }
}

ParallaxBackground::~ParallaxBackground() {
    for (auto texture : layers) {
        SDL_DestroyTexture(texture);
    }
}

void ParallaxBackground::scroll(int scrollSpeed) {
    yOffset += scrollSpeed;
    if (yOffset > totalHeight) {
        yOffset = 0;
    }
}

void ParallaxBackground::render() {
    int y = yOffset;
    for (SDL_Texture* texture : layers) {
        SDL_Rect dstRect = { 0, y, 800, 600 }; // Adjust the destination rect as needed
        SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
        y += 600; // Adjust this value based on your window height
    }
}
