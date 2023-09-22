#include "player.h"

#include "../game.h"
#include "../global.h"
#include "../resourcemanager.h"
#include "../entitymanager.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

Player::Player(int x, int y) : playerX(x), playerY(y) {};

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
}

void Player::render() {
    texture = global::resourceManager()->getResourceAsTexture(raw_enum(global::Res::PlayerSprite));
	global::game()->blit(texture, playerX, playerY);
}


void Player::save() const
{

}

void Player::load()
{

}