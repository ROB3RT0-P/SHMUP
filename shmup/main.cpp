/*******************************************
	Written by Robert Parry [RJP] - 2023
*******************************************/

/*********************************************************************************
	Copyright (c) Robert Parry - 2023

	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1. The origin of this software must not be misrepresented; you must not
	claim that you wrote the original software. If you use this software
	in a product, an acknowledgment in the product documentation would be
	appreciated but is not required.

	2. Altered source versions must be plainly marked as such, and must not be
	misrepresented as being the original software.

	3. This notice may not be removed or altered from any source
	distribution.
*********************************************************************************/

/*********************************************************************************
	RJP - TODO: 
		Priority:
				- renderer.h
				- Render enemies
				- Rewrite move()
				- Collision
		Non-Priority:
				- Switch to entity manager
				- Game over text
				- Game over music
				- Code cleanup - Variable names
				- Pulse text not fading correctly
				- Switch to stateManager.cpp
				- Refactor process manager so that the code it's calling
				  is called directly instead.
				- Rewrite debugText so that each letter is it's 
				  own texture and then render them separately.
				- Write a vector2D class for the player's position.
*********************************************************************************/

#include "global.h"
#include "game.h"
#include "processmanager.h"
#include "entitymanager.h"
#include "resourcemanager.h"
#include "controls.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

namespace global
{

namespace // hidden namespace
{
	Game* GameInstance;
	ProcessManager* ProcessManagerInstance;
	EntityManager* EntityManagerInstance;
	ResourceManager* ResourceManagerInstance;


	ResourceManager::ResourceDBEntry resourceDatabase[] =
	{
		{ raw_enum(Res::Default),			"texture.png",								ResourceManager::ResourceType::Texture },
		{ raw_enum(Res::PlayerSprite),		"kenny/Ships/ship_0001.png",				ResourceManager::ResourceType::Texture },
		{ raw_enum(Res::EnemySprite),		"kenny/Ships/ship_0002.png",				ResourceManager::ResourceType::Texture },
	};
}
	Game* game() { return GameInstance; }
	ProcessManager* processManager() { return ProcessManagerInstance; }
	EntityManager* entityManager() { return EntityManagerInstance; }
	ResourceManager* resourceManager() { return ResourceManagerInstance; }
}

int main( int argc, char* args[] )
{
	global::GameInstance = new Game();
	global::EntityManagerInstance = new EntityManager();
	global::ProcessManagerInstance = new ProcessManager();
	global::ResourceManagerInstance = new ResourceManager();
	
	global::resourceManager()->initializeResourceDatabase(global::resourceDatabase, sizeof(global::resourceDatabase) / sizeof(global::resourceDatabase[0]), raw_enum(global::Res::Max), "./Data/");

	if( !global::game()->initialize(540, 960))
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		{	
			bool quit = false;
			Uint32 prevTicks = SDL_GetTicks();

			while( !quit )
			{
				Uint32 currentTicks = SDL_GetTicks();
				float deltaTime = (currentTicks - prevTicks) / 1000.f;
				prevTicks = currentTicks;

				global::game()->tickLogic(deltaTime);

				global::game()->renderAndPresent();

				global::game()->postFrameUpdate();

				quit = global::game()->handleEvents(deltaTime);
			}
		}
	}

	global::game()->close();

	return 0;
}