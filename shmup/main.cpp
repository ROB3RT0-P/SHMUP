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

	//Start up SDL and create window
	if( !global::game()->initialize(640, 480))
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		{	
			//Main loop flag
			bool quit = false;

			//While application is running
			while( !quit )
			{
				global::game()->tickLogic();

				global::game()->renderAndPresent();

				global::game()->postFrameUpdate();
			
			}
		}
	}

	//Free resources and close SDL
	global::game()->close();

	return 0;
}