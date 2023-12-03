/*******************************************
	Written by Robert Parry [RJP] - 2023
	Refer to main.cpp for the license
*******************************************/

#pragma once

#include "../shmup/entities/player.h"
#include <SDL.h>

class Controls
{
	public:
		Controls(Player& player);

		int handleInput(SDL_Event& event, float deltaTime);

	private:
		Player& player;
};