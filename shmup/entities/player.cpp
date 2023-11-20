#include "player.h"

#include "../game.h"
#include "../global.h"
#include "../resourcemanager.h"
#include "../entitymanager.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

Player::Player(float x, float y) : playerX(x), playerY(y) {};

static IEntity* playerEntityCreateFunc(void* user) {
	Player* playerEntity = new Player();
	// Should be already loaded but increases the ref count
	global::resourceManager()->loadResource(raw_enum(global::Res::PlayerSprite));

	return playerEntity;
}

static IEntity* playerEntityDestroyFunc(IEntity* entity, void* user) 
{
	delete static_cast<Player*>(entity);

	global::resourceManager()->unloadResource(raw_enum(global::Res::PlayerSprite));

	return NULL;
}

void Player::registerWithEntityManager() 
{
	global::entityManager()->registerEntityCreator(raw_enum(global::EntityType::Player), playerEntityCreateFunc, playerEntityDestroyFunc, NULL);
}

void Player::init()
{
    texture = nullptr;
    playerX = 0;
    playerY = 0;
	playerVelocityX = 0;
	playerVelocityY = 0;
	playerAcceleration = 1;
}

void Player::update(float deltaTime)
{
	playerVelocityX = SDL_clamp(playerVelocityX, -playerSpeed, playerSpeed);
	playerVelocityY = SDL_clamp(playerVelocityY, -playerSpeed, playerSpeed);

	playerX += playerVelocityX * deltaTime;
	playerY += playerVelocityY * deltaTime;

	checkBounds();
}

void Player::move(int newX, int newY, float deltaTime)
{
	// Calculate the distance to move based on playerSpeed and deltaTime
	float moveDistance = playerSpeed * deltaTime;

	// Calculate the target position after movement
	float targetX = playerX + (newX * moveDistance);
	float targetY = playerY + (newY * moveDistance);

	// Interpolate between current position and target position
	playerX = lerp(playerX, targetX, deltaTime);
	playerY = lerp(playerY, targetY, deltaTime);

	checkBounds();
}

float Player::lerp(float start, float end, float t)
{
	return start + t * (end - start);
}

void Player::checkBounds()
{
	if (playerX < 40.0f) playerX = 40.0f;
	if (playerY < 40.0f) playerY = 40.0f;
	if (playerX > (540.0f - boundOffset)) playerX = (540.0f - boundOffset);
	if (playerY > (960.0f - boundOffset)) playerY = (960.0f - boundOffset);
}

void Player::render() {
	texture = global::resourceManager()->getResourceAsTexture(raw_enum(global::Res::PlayerSprite));
	global::game()->blit(texture, iPlayerX, iPlayerY);
}

void Player::save() const
{

}

void Player::load()
{

}