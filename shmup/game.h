#pragma once

#include "loadingprocess.h"
#include "entities/player.h"
#include "controls.h"

#include <string>

// Forwards
struct SDL_Texture;
struct SDL_Window;
struct SDL_Renderer;

class Game : 
	public LoadingProcess::ILoadingProcessCallback, 
	public IProcess
{
public:
	Game() : quit(false), player(640 * 0.5, 480 * 0.9), controls(player) {} //RJP - hardcoded for now - Change this

	bool initialize(int ScreenWidth, int ScreenHeight);
	void tickLogic();
	void blit(SDL_Texture* texture, int x, int y);
	void renderAndPresent();
	void postFrameUpdate();
	void close();

private:
	bool loadInitialResources();

	virtual void start(const Info& info);;
	virtual void tick(const Info& info) {};
	virtual void render(const Info& info);
	virtual void endOfFrameUpdate(const Info& info) {};
	virtual void completed(const Info& info) {};

	virtual void onLoadComplete(LoadingProcess::LoadRequest* loadedResources, size_t count);

	void handleEvents();

	//Screen dimension constants
	int SCREEN_WIDTH = 0;
	int SCREEN_HEIGHT = 0;

	LoadingProcess loadingProcess;

	Player* playerEntity = NULL;

	SDL_Window* gWindow = NULL; //The window we'll be rendering to
	SDL_Renderer* gRenderer = NULL; //The window renderer	
	SDL_Texture* gTexture = NULL; //Current displayed texture

	bool quit;
	Player player;
	Controls controls;
};
