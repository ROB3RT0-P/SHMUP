#include "titleScreen.h"

TitleScreen::TitleScreen(SDL_Renderer* renderer, int screenWidth, int screenHeight) {
    this->renderer = renderer;
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
}

TitleScreen::~TitleScreen() {
    SDL_DestroyTexture(backgroundTexture);
}

void TitleScreen::handleEvents() {
   
}

void TitleScreen::update() {
    // Update logic for the title screen
}

void TitleScreen::render() {
    // Clear the renderer
    SDL_RenderClear(renderer);

    // Render the title screen background
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);

    // Additional rendering code can be added here

    // Present the renderer
    SDL_RenderPresent(renderer);
}
