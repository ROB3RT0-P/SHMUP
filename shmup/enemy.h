/*******************************************
	Written by Robert Parry [RJP] - 2023
	Refer to main.cpp for the license
*******************************************/

#pragma once

#include "entitymanager.h"
//#include "game.h"
#include "renderer.h"
#include "global.h"
#include "resourcemanager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <vector>

class Game; // RJP - Forward declaration of game

struct SDL_Texture;

class Enemy
{
public:
	Enemy(float screenWidth, float screenHeight);

	void init(float screenWidth, float screenHeight, SDL_Renderer& renderer)
	{
		fEnemyX_ = static_cast<float>(rand() % static_cast<int>(screenWidth + 20.0f));
		fEnemyY_ = fDefaultEnemyPosY_;

		fTargetPosX_ = static_cast<float>(rand() % static_cast<int>(screenWidth));
		fTargetPosY_ = screenHeight + 20;

		textureRenderer = new Renderer(&renderer);
	}
	void render();	
	void update(float deltaTime);
	Enemy createEnemies( float screenWidth, float screenHeight, int numEnemies );
	float lerp(float start, float end, float t);
	bool checkBounds(float screenWidth, float screenHeight);
	
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
	SDL_Texture* tTexture = NULL;
	Renderer* textureRenderer;

	float fTargetPosY_;
	float fTargetPosX_;
	float fEnemyY_;
	float fEnemyX_;
	int iEnemySpeed_ = 10;
	float fDefaultEnemyPosY_ = -20;

};