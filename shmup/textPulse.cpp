/*******************************************
    Written by Robert Parry [RJP] - 2023
*******************************************/

#include "textPulse.h"

PulseText::PulseText(SDL_Renderer* renderer, const std::string& fontPath, int fontSize, SDL_Color textColor)
    : renderer(renderer), font(font), text(text), x(x), y(y), scaleFactor(1.0f), increasing(true), scale(255)
{
    font = TTF_OpenFont(fontPath.c_str(), fontSize);

    textColor = { 255, 255, 255, static_cast<Uint8>(scaleFactor) };
    
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), { 255, 255, 255 });
    if (surface == nullptr) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Surface missing.", SDL_GetError(), nullptr);
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Texture missing.", SDL_GetError(), nullptr);
        SDL_FreeSurface(surface);
    }
}

PulseText::~PulseText() 
{
    SDL_DestroyTexture(texture);
}

void PulseText::Update(float deltaTime) 
{
    const float pulseSpeed = 0.5f;
    
    if (increasing) {
        scaleFactor += pulseSpeed * deltaTime;
        if (scaleFactor >= 254.0f) {
            scaleFactor = 1.5f;
            increasing = false;
            
        }
    }
    else {
        scaleFactor -= pulseSpeed * deltaTime;
        if (scaleFactor <= 1.0f) {
            scaleFactor = 1.0f;
            increasing = true;
        }
    }
}

void PulseText::Render(const std::string& text, int x, int y) 
{
    SDL_Rect destRect = { x, y, static_cast<int>(text.length() * 10 ), 30 };
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}
