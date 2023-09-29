#include "Enemy.h"
#include <cstdlib>
#include <ctime>

Enemy::Enemy(SDL_Renderer* renderer, int screenWidth, int screenHeight) : renderer(renderer) {
    width = 50;
    height = 50;
    x = rand() % (screenWidth - width);
    y = rand() % (screenHeight - height);
    speed = 2;
}

void Enemy::move() {
    // Move the enemy horizontally (customize movement logic as needed)
    x += speed;
}

void Enemy::draw() {
    SDL_Rect enemyRect = { x, y, width, height };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
    SDL_RenderFillRect(renderer, &enemyRect);
}
