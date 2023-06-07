#include "game.h"
#include "global.h"
#include "processmanager.h"
#include "resourcemanager.h"
#include "entitymanager.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

bool Game::initialize(int ScreenWidth, int ScreenHeight)
{
	bool success = true;
	SCREEN_WIDTH = ScreenWidth;
	SCREEN_HEIGHT = ScreenHeight;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				global::resourceManager()->initializeLoaderData(gRenderer);
			}
		}
	}

	return success && loadInitialResources();
}

bool Game::loadInitialResources()
{
	loadingProcess.callback = this;
	LoadingProcess::LoadRequest toLoad;
	toLoad.resource = global::Res::Default;
	loadingProcess.dataToLoad.push_back(toLoad);
	toLoad.resource = global::Res::PlayerSprite;
	loadingProcess.dataToLoad.push_back(toLoad);

	global::processManager()->registerProcess(&loadingProcess, raw_enum(global::TaskID::Loading), raw_enum(global::TickOrder::DontCare), raw_enum(global::RenderOrder::DontCare));

	return true;
}

void Game::start(const Info& info) {
	playerEntity = static_cast<Player*>(global::entityManager()->createEntity(raw_enum(global::EntityType::Player)));
}

void Game::tickLogic() {
	global::processManager()->tickProcesses();
}

void Game::renderAndPresent()
{
	//Clear screen
	SDL_RenderClear(gRenderer);

	global::processManager()->renderProcesses();

	//Update screen
	SDL_RenderPresent(gRenderer);
}

void Game::postFrameUpdate()
{
	global::processManager()->endOfFrameCleanup();
}

void Game::close()
{
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void Game::render(const Info& info)
{
	//Render texture to screen
	//SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
	playerEntity->render();
}

void Game::onLoadComplete(LoadingProcess::LoadRequest* loadedResources, size_t count)
{
	gTexture = global::resourceManager()->getResourceAsTexture(raw_enum(global::Res::Default));
	global::processManager()->registerProcess(this, raw_enum(global::TaskID::DontCare), raw_enum(global::TickOrder::DontCare), raw_enum(global::RenderOrder::DontCare));
}
