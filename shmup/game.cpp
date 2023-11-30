/*******************************************
	Written by Robert Parry [RJP] - 2023
*******************************************/

#include "game.h"

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
		gWindow = SDL_CreateWindow("SHMUP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

	imagePaths = { "shmupBackground.bmp", "", "" };
	titleImagePaths = { "titleBackground.bmp", "", "" };
	background = new ParallaxBackground(gRenderer, imagePaths, 1);
	titleBackground = new ParallaxBackground(gRenderer, titleImagePaths, 1);

	textColor = { 255, 255, 255, 255 };
	debugText = new DebugText(gRenderer, "Data/kenny/Fonts/kenneyBlocks.ttf", 25, textColor);
	pulseText = new PulseText(gRenderer,"Data/kenny/Fonts/kenneyBlocks.ttf", 10, textColor);
	
	playerEntity = new Player( fScreenWidth / 2, fScreenHeight / 2 );
	audio = new AudioPlayer();
	audio->play("Data/titleScreen.mp3");
	controls = new Controls(*playerEntity);
	return true;
}

void Game::start(const Info& info) {
	//playerEntity = static_cast<Player*>(global::entityManager()->createEntity(raw_enum(global::EntityType::Player)));
	currentState = GameState::START;

	if (playerEntity)
	{
		playerEntity->init();
		playerEntity->setPlayerHealth( 100 );
	}
}

void Game::tickLogic(float deltaTime) {
	global::processManager()->tickProcesses();

	switch (currentState) {
	case GameState::START:
		titleBackground->randMovement(0);
		pulseText->Update(deltaTime);
		Game::handleEvents(deltaTime);
		break;

	case GameState::PLAY:
		Game::handleEvents(deltaTime);
		playerEntity->update(deltaTime);
		background->scroll(3);
		break;

	case GameState::PAUSE:
		Game::handleEvents(deltaTime);
		break;
	}
}

void Game::blit(SDL_Texture* texture, float x, float y)
{
	SDL_Rect dest;

	dest.x = static_cast<int>(x);
	dest.y = static_cast<int>(y);
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	SDL_RenderCopy(gRenderer, texture, NULL, &dest);
}

void Game::renderAndPresent()
{	
	SDL_RenderClear(gRenderer);
	global::processManager()->renderProcesses();
	SDL_RenderPresent(gRenderer);
	global::processManager()->renderProcesses();
	SDL_RenderPresent(gRenderer);
}

void Game::render(const Info& info)
{
	playerTexture = global::resourceManager()->getResourceAsTexture(raw_enum(global::Res::PlayerSprite));

	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
	
	playerScore = std::to_string(SDL_GetTicks() / 100);

	if (playerEntity != nullptr)
	{
		playerEntityHealth = std::to_string(playerEntity->getPlayerHealth());
	}

	switch (currentState) {
	case GameState::START:
		titleBackground->titleRender();
		debugText->RenderText("GALACTIC HAVOC", (SCREEN_WIDTH / 4) + 25, SCREEN_HEIGHT / 3);
		pulseText->Render("Press Start", (SCREEN_WIDTH / 4) + 25, SCREEN_HEIGHT / 2);
		break;

	case GameState::PLAY:
		background->render();
		debugText->RenderText("Score: " + playerScore, 10, 10);
		debugText->RenderText("Ship Health: " + playerEntityHealth, 10, 40);

		if (SDL_GetTicks() < 5000 && SDL_GetTicks() > 1000)
		{
			debugText->RenderText("Mission Start", (SCREEN_WIDTH / 2) - 110, SCREEN_HEIGHT / 2);
			debugText->RenderText("Objective: Dodge or Destroy",
				(SCREEN_WIDTH / 2) - 210, (SCREEN_HEIGHT / 2) + 40);
		}

		blit(playerTexture, playerEntity->getPlayerX(), playerEntity->getPlayerY());
		SDL_assert(playerTexture);
		break;

	case GameState::PAUSE:
		break;
	}
}

void Game::postFrameUpdate()
{
	global::processManager()->endOfFrameCleanup();
}

void Game::close()
{
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

bool Game::handleEvents(float deltaTime) {
	while (SDL_PollEvent(&event) != 0)
	{
		// RJP - This could do with optimising.
		controls->handleInput(event, deltaTime);

		if (controls->handleInput(event, deltaTime) == 1)
		{
			return true;
		}
		else if (controls->handleInput(event, deltaTime) == 2 && currentState == GameState::START)
		{
			currentState = GameState::PLAY;
			return false;
		}

		// RJP - Not sure if I will implement this.
		/*
		else if (controls.handleInput(event, deltaTime) == 2 && currentState == GameState::PLAY)
		{
			currentState = GameState::PAUSE;
		}
		else if (controls.handleInput(event, deltaTime) == 2 && currentState == GameState:PAUSE)
		{
			currentState = GameState::PAUSE;
		}
		*/
	}

	return 0;
}

void Game::onLoadComplete(LoadingProcess::LoadRequest* loadedResources, size_t count)
{
	gTexture = global::resourceManager()->getResourceAsTexture(raw_enum(global::Res::Default));
	global::processManager()->registerProcess(this, raw_enum(global::TaskID::DontCare), raw_enum(global::TickOrder::DontCare), raw_enum(global::RenderOrder::DontCare));
}
