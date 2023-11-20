#include "generatedBackground.h"
#include <cstdlib>
#include <ctime>

GeneratedBackground::GeneratedBackground(SDL_Renderer* renderer, int screenWidth, int screenHeight, int starCount)
: renderer(renderer), screenWidth(screenWidth), screenHeight(screenHeight) {
		createStars(starCount);
}

void GeneratedBackground::createStars(int starCount) 
{
	std::srand(std::time(0));

	for (int i = 0; i < starCount; ++i) {
		stars.push_back({ 
			static_cast<float>(std::rand() % screenWidth), 
			static_cast<float>(std::rand() % screenHeight), 
			static_cast<float>(std::rand() % 100 + 50),
			static_cast<float>(std::rand() % 12 + 0.1) });
	}
}

void GeneratedBackground::updateStars(float deltaTime)
{
	for (auto& star : stars) {
		star.y += star.speed * deltaTime;

		if (star.y > screenHeight) {
			star.y = 0;
			star.x = static_cast<float>(std::rand() % screenWidth);
		}
	}
}

void GeneratedBackground::renderStars(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (const auto& star : stars) {
		SDL_Rect starRect = {
			static_cast<int>(star.x),
			static_cast<int>(star.y),
			static_cast<int>(star.size),
			static_cast<int>(star.size)
		};
	}
}