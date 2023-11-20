#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>

class GeneratedBackground
{
public:

	GeneratedBackground(SDL_Renderer* renderer, int screenWidth, int screenHeight, int starCount);

	void updateStars(float deltaTime);
	void renderStars(SDL_Renderer* renderer);

private:
    struct Star {
        float x, y;
        float size;
        float speed;
    };

    SDL_Renderer* renderer;
    int screenWidth, screenHeight;
    std::vector<Star> stars;

    void createStars(int starCount);
};