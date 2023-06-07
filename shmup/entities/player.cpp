#include "player.h"

#include "../global.h"
#include "../resourcemanager.h"
#include "../entitymanager.h"

static IEntity* playerEntityCreateFunc(void* user) {
	Player* playerEntity = new Player();
	// Should be already loaded but increases the ref count
	global::resourceManager()->loadResource(raw_enum(global::Res::PlayerSprite));

	playerEntity->texture = global::resourceManager()->getResourceAsTexture(raw_enum(global::Res::PlayerSprite));

	return playerEntity;
}

static IEntity* playerEntityDestroyFunc(IEntity* entity, void* user) {
	delete static_cast<Player*>(entity);

	global::resourceManager()->unloadResource(raw_enum(global::Res::PlayerSprite));

	return NULL;
}

void Player::registerWithEntityManager() {
	global::entityManager()->registerEntityCreator(raw_enum(global::EntityType::Player), playerEntityCreateFunc, playerEntityDestroyFunc, NULL);
}

void Player::render() {

}

void Player::save() const {

}

void Player::load() {

}

