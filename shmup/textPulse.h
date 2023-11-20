#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class PulseText {
public:
    PulseText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y);
    ~PulseText();

    void Update(float deltaTime);
    void Render();

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Texture* texture;
    std::string text;
    int x, y;
    float scaleFactor;
    bool increasing;

    void CreateTexture();
};