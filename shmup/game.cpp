#include "game.h"
#include "global.h"
#include "processmanager.h"
#include "resourcemanager.h"
#include "entitymanager.h"
#include "parallaxBackground.h"
#include "debugText.h"

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
	Game::handleEvents();
}

void Game::blit(SDL_Texture* texture, int x, int y)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	SDL_RenderCopy(gRenderer, texture, NULL, &dest);
}

void Game::renderAndPresent()
{
	//Set the background colour to blue
	//SDL_SetRenderDrawColor(gRenderer, 96, 180, 255, 255);

	//Clear screen
	SDL_RenderClear(gRenderer);

	global::processManager()->renderProcesses();

	//Debug Text
	SDL_Color textColor = { 255, 255, 255, 255 };
	DebugText debugText(gRenderer, "Data/kenny/Fonts/kenneyBlocks.ttf", 24, textColor);
	
	// Render debug text
	debugText.RenderText("Shmup", 10, 10);

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

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		controls.handleInput(event);
	}
}

void Game::render(const Info& info)
{
	//Rendered in order
	
	//Parallax Background
	std::vector<std::string> imagePaths = { "shmupBackground.bmp", "", "" };
	int scrollSpeed = 1; // Adjust as needed

	// Initialize the ParallaxBackground
	ParallaxBackground background(gRenderer, imagePaths, scrollSpeed);
	background.scroll(scrollSpeed);
	background.render();
	

	//Player render
	SDL_Texture* playerTexture = global::resourceManager()->getResourceAsTexture(raw_enum(global::Res::PlayerSprite));
	blit(playerTexture, player.getPlayerX(), player.getPlayerY());
}

void Game::onLoadComplete(LoadingProcess::LoadRequest* loadedResources, size_t count)
{
	gTexture = global::resourceManager()->getResourceAsTexture(raw_enum(global::Res::Default));
	global::processManager()->registerProcess(this, raw_enum(global::TaskID::DontCare), raw_enum(global::TickOrder::DontCare), raw_enum(global::RenderOrder::DontCare));
}
