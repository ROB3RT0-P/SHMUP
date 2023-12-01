/*******************************************
    Written by Robert Parry [RJP] - 2023
*******************************************/

#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class PulseText {
public:
    PulseText(SDL_Renderer* renderer, const std::string& fontPath, int fontSize, SDL_Color textColor, const std::string text);
    ~PulseText();

    void Update(float deltaTime);
    void Render(int x, int y);

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Texture* texture;
    std::string text;
    int x, y;
    float scaleFactor;
    bool increasing;

    SDL_Color textColor;
    Uint8 scale;
};