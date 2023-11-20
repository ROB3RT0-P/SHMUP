#pragma once

#include "../entity.h"

#include <iostream>

struct SDL_Texture;

class Player : public IEntity
{
public:
	static void registerWithEntityManager();
	
	Player(float x, float y);

	void init();
	void render();
	void update(float deltaTime);
	void move(int newX, int newY, float deltaTime);
	float lerp(float start, float end, float t);
	void checkBounds();

	void setPlayerX(float newPosX) { playerX = newPosX; }
	void setPlayerY(float newPosY) { playerY = newPosY; }

	int getPlayerX() { return iPlayerX; }
	int getPlayerY() { return iPlayerY; }

	Player() = default;
	~Player() {};

	int getPlayerHealth() { return playerHealth; }
	void damagePlayerHealth(int damage) { playerHealth -= damage; }
	void setPlayerHealth(int healthAmount)
	{
		playerHealth += healthAmount;
		if (playerHealth > 100) { playerHealth = 100; }
	}

	SDL_Texture& getTexture() { return *texture; }
	float playerY;
	float playerX;
	float playerAcceleration = 10000.0f;
	float playerVelocityX, playerVelocityY;
private:

	float playerSpeed = 2500.0f;
	int playerHealth = 100;
	float boundOffset = 10.0f;

	int iPlayerX = static_cast<int>(playerX);
	int iPlayerY = static_cast<int>(playerY);

	friend IEntity* playerEntityCreateFunc(void* user);
	friend IEntity* playerEntityDestroyFunc(IEntity* entity, void* user);

	virtual void save() const;
	virtual void load();

	bool saveHighScore(int highScore) const;
	int loadHighScore();

	SDL_Texture* texture = NULL;
};