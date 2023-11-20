#include "Enemy.h"

#include "game.h"
#include "global.h"
#include "resourcemanager.h"
#include "entitymanager.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

Enemy::Enemy(int x, int y) : EnemyX(x), EnemyY(y) {};

void Enemy::init()
{
	texture = nullptr;
	EnemyX = 0;
	EnemyY = 0;
}

void Enemy::render() 
{
	texture = global::resourceManager()->getResourceAsTexture(raw_enum(global::Res::EnemySprite));
	global::game()->blit(texture, EnemyX, EnemyY);
}

void Enemy::move() 
{

}