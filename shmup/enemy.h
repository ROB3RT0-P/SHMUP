#pragma once

#include <iostream>

struct SDL_Texture;

class Enemy
{
public:
	Enemy(int x, int y);

	void init();
	void render();
	void move();
	
	void setEnemyX(int newPosX) { EnemyX += newPosX; }
	void setEnemyY(int newPosY) { EnemyY += newPosY; }

	int getEnemyX() { return EnemyX; }
	int getEnemyY() { return EnemyY; }

	Enemy() = default;
	~Enemy() {};

	void move(int newX, int newY) {
		EnemyX += (newX * EnemySpeed);
		EnemyY += (newY * EnemySpeed);
	};

	SDL_Texture& getTexture() { return *texture; }

private:
	int EnemyY;
	int EnemyX;
	int EnemySpeed = 10;

	SDL_Texture* texture = NULL;
};