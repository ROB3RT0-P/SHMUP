#pragma once

#ifndef CONTROLS_H
#define CONTROLS_H

#include "../shmup/entities/player.h"
#include <sdl.h>

class Controls
{
	public:
		Controls(Player& player);

		void handleInput(SDL_Event& event);

	private:
		Player& player;
};


#endif //CONTROLS_H