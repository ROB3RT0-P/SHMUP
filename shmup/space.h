#pragma once

#include <SDL.h>
#include <vector>
#include <random>

struct Star {
    float x, y, depth, size;
};

class Space {
public:
    Space(SDL_Renderer* renderer, int screenWidth, int screenHeight, int numStars, int numDistantStars);
    ~Space();

    bool IsInitialized() const;
    void Init();
    void Render(SDL_Renderer* spaceRenderer);
    void Update(float deltaTime);

private:
    SDL_Renderer* renderer;
    int screenWidth;
    int screenHeight;
    int numStars;
    int numDistantStars;
    int numStaticStars;
    std::vector<Star> stars;
    std::vector<Star> distantStars;
    std::default_random_engine randomEngine;
    float maxDepth;
};