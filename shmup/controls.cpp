#include <SDL.h>
#include "controls.h"

Controls::Controls(Player& player) : player(player) {}

void Controls::handleInput(SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:
            player.move(-1, 0);
            break;
        case SDLK_RIGHT:
            player.move(1, 0);
            break;
        case SDLK_UP:
            player.move(0, -1);
            break;
        case SDLK_DOWN:
            player.move(0, 1);
            break;
        case SDLK_ESCAPE:
            SDL_Quit();
        }
    }
}
