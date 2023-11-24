#ifndef GAME_H
#define GAME_H

#include "loadingprocess.h"
#include "entities/player.h"
#include "controls.h"
#include "parallaxBackground.h"
#include "textPulse.h"
#include "generatedBackground.h"
#include "space.h"
#include <string>
#include "audio.h"

// Forwards
struct SDL_Texture;
struct SDL_Window;
struct SDL_Renderer;

enum class GameState
{
	START,
	PLAY,
	PAUSE
};

class Game : 
	public LoadingProcess::ILoadingProcessCallback, 
	public IProcess
{
public:
	Game() : quit(false), playerEntity() {}

	bool initialize(int ScreenWidth, int ScreenHeight);
	void tickLogic(float deltaTime);
	void blit(SDL_Texture* texture, float x, float y);
	void renderAndPresent();
	void postFrameUpdate();
	void close();
	bool handleEvents(float deltaTime);

private:
	bool loadInitialResources();

	virtual void start(const Info& info);;
	virtual void tick(const Info& info) {};
	virtual void render(const Info& info);
	virtual void endOfFrameUpdate(const Info& info) {};
	virtual void completed(const Info& info) {};

	virtual void onLoadComplete(LoadingProcess::LoadRequest* loadedResources, size_t count);

	int SCREEN_WIDTH = 0;
	int SCREEN_HEIGHT = 0;

	float fScreenWidth = static_cast<float>(SCREEN_WIDTH);
	float fScreenHeight = static_cast<float>(SCREEN_HEIGHT);

	LoadingProcess loadingProcess;

	Player* playerEntity;

	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;
	SDL_Texture* gTexture = NULL;

	bool quit;
	Controls* controls;
	ParallaxBackground* background;
	ParallaxBackground* titleBackground;
	GeneratedBackground* starBackground;

	int scrollSpeed = 1;
	std::vector<std::string> imagePaths;
	std::vector<std::string> titleImagePaths;
	TTF_Font* font;
	PulseText* pulseText;
	SDL_Texture* playerTexture;
	Space* spaceBackground;

	GameState currentState = GameState::START;

	SDL_Color textColor;
	std::string playerScore;
	std::string playerEntityHealth;

	SDL_Event event;

	AudioPlayer* audio;
};

#endif //Game