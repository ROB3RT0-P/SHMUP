#pragma once

#include "../entity.h"

struct SDL_Texture;

class Player : public IEntity
{
public:

	static void registerWithEntityManager();

	void render();

private:

	Player() = default;
	~Player() {};

	friend IEntity* playerEntityCreateFunc(void* user);
	friend IEntity* playerEntityDestroyFunc(IEntity* entity, void* user);

	virtual void save() const;
	virtual void load();

	SDL_Texture* texture = NULL;

};