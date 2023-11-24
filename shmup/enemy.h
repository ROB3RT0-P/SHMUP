#pragma once
#include <iostream>
#include <vector>

struct SDL_Texture;

class Enemy
{
public:
	Enemy( float screenWidth, float screenHeight ) 
	{
		fEnemyX_ = static_cast<float>(rand() % static_cast<int>(screenWidth + 20.0f));
		fEnemyY_ = fDefaultEnemyPosY_;
	};

	void init();
	void render();
	void move();
	void createEnemies( float screenWidth, float screenHeight, int numEnemies );
	float lerp(float start, float end, float t);
	void move(int newX, int newY, float deltaTime);
	
	
	void setEnemyX(float newPosX) { fEnemyX_ += newPosX; }
	void setEnemyY(float newPosY) { fEnemyY_ += newPosY; }

	float getEnemyX() { return fEnemyX_; }
	float getEnemyY() { return fEnemyY_; }

	Enemy() = default;
	~Enemy() {};

	void move(int newX, int newY) {
		fEnemyX_ += (newX * iEnemySpeed_);
		fEnemyY_ += (newY * iEnemySpeed_);
	};

	SDL_Texture& getTexture() { return *tTexture; }

private:
	float fEnemyY_;
	float fEnemyX_;
	int iEnemySpeed_ = 10;
	float fDefaultEnemyPosY_ = -20;

	std::vector<Enemy> vEnemies;

	SDL_Texture* tTexture = NULL;
};