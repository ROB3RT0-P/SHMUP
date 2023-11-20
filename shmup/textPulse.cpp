#include "textPulse.h"

PulseText::PulseText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y)
    : renderer(renderer), font(font), text(text), x(x), y(y), scaleFactor(1.0f), increasing(true) {
    CreateTexture();
}

PulseText::~PulseText() {
    SDL_DestroyTexture(texture);
}

void PulseText::CreateTexture() {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), { 255, 255, 255 });
    if (surface == nullptr) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Surface missing.", SDL_GetError(), nullptr);
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Texture missing.", SDL_GetError(), nullptr);
    }

    SDL_FreeSurface(surface);
}

void PulseText::Update(float deltaTime) {
    const float pulseSpeed = 0.5f;

    if (increasing) {
        scaleFactor += pulseSpeed * deltaTime;
        if (scaleFactor >= 1.5f) {
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

void PulseText::Render() {
    SDL_Rect destRect = { x, y, static_cast<int>(text.length() * 10 * scaleFactor), 30 };
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}
