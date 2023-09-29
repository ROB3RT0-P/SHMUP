#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>

class Enemy {
public:
    Enemy(SDL_Renderer* renderer, int screenWidth, int screenHeight);

    void move();
    void draw();

private:
    int x, y;
    int width, height;
    int speed;
    SDL_Renderer* renderer;
};

#endif
