#pragma once

#include "../entity.h"

#include <iostream>

struct SDL_Texture;

class Player : public IEntity
{
public:
	static void registerWithEntityManager();
	
	Player(int x, int y);

	void init();
	void render();

	void setPlayerX(int newPosX) { playerX += newPosX; }
	void setPlayerY(int newPosY) { playerY += newPosY; }

	int getPlayerX() { return playerX; }
	int getPlayerY() { return playerY; }

	Player() = default;
	~Player() {};

	void move(int newX, int newY) {
		playerX += (newX * playerSpeed);
		playerY += (newY * playerSpeed);
	};

	SDL_Texture& getTexture() { return *texture; }

private:
	int playerY;
	int playerX;
	int playerSpeed = 10;

	friend IEntity* playerEntityCreateFunc(void* user);
	friend IEntity* playerEntityDestroyFunc(IEntity* entity, void* user);

	virtual void save() const;
	virtual void load();

	bool saveHighScore(int highScore) const;
	int loadHighScore();

	SDL_Texture* texture = NULL;
};