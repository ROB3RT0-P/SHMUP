/*******************************************
	Written by Robert Parry [RJP] - 2023
	Refer to main.cpp for the license
*******************************************/

#include "enemy.h"


void Enemy::update(float deltaTime)
{
	// Calculate the distance to move based on playerSpeed and deltaTime
	float moveDistance = iEnemySpeed_ * deltaTime;

	// Calculate the target position after movement
	float targetX = fEnemyX_ + (fTargetPosX_ * moveDistance);
	float targetY = fEnemyY_ + (fTargetPosY_ * moveDistance);

	// Interpolate between current position and target position
	fEnemyX_ = lerp(fEnemyX_, targetX, deltaTime);
	fEnemyY_ = lerp(fEnemyY_, targetY, deltaTime);
}

float Enemy::lerp(float start, float end, float t)
{
	return start + t * (end - start);
}

bool Enemy::checkBounds(float screenWidth, float screenHeight)
{
	if (fEnemyY_ > screenHeight)
	{
		return true;
	}
	return false;
}

void Enemy::render() 
{
	tTexture = global::resourceManager()->getResourceAsTexture(raw_enum(global::Res::EnemySprite));
	//global::game()->blit(tTexture, fEnemyX_, fEnemyY_);
	textureRender->
}