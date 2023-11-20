#include "global.h"
#include "game.h"
#include "processmanager.h"
#include "entitymanager.h"
#include "resourcemanager.h"
#include "controls.h"

//Using SDL, SDL_image, standard IO, and strings
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