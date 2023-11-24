#include "Enemy.h"

#include "game.h"
#include "global.h"
#include "resourcemanager.h"
#include "entitymanager.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

void Enemy::init()
{

}

void Enemy::move(int newX, int newY, float deltaTime)
{
	// Calculate the distance to move based on playerSpeed and deltaTime
	float moveDistance = iEnemySpeed_ * deltaTime;

	// Calculate the target position after movement
	float targetX = fEnemyX_ + (newX * moveDistance);
	float targetY = fEnemyY_ + (newY * moveDistance);

	// Interpolate between current position and target position
	fEnemyX_ = lerp(fEnemyX_, targetX, deltaTime);
	fEnemyY_ = lerp(fEnemyY_, targetY, deltaTime);


}

float Enemy::lerp(float start, float end, float t)
{
	return start + t * (end - start);
}

void Enemy::createEnemies( float screenWidth, float screenHeight, int numEnemies )
{
	for (int i = 0; i < numEnemies; ++i)
	{
		vEnemies.push_back(Enemy(screenWidth, screenHeight));
	}
}

void Enemy::render() 
{
	tTexture = global::resourceManager()->getResourceAsTexture(raw_enum(global::Res::EnemySprite));
	global::game()->blit(tTexture, fEnemyX_, fEnemyY_);
}

void Enemy::move() 
{

}