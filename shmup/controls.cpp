#include <SDL.h>
#include "controls.h"

Controls::Controls(Player& player) : player(player) {}

int Controls::handleInput(SDL_Event& event, float deltaTime)
{
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                player.playerVelocityX = -player.playerAcceleration;
                return 0;
                break;
            case SDLK_RIGHT:
                player.playerVelocityX = player.playerAcceleration;
                return 0;
                break;
            case SDLK_UP:
                player.playerVelocityY = -player.playerAcceleration;
                return 0;
                break;
            case SDLK_DOWN:
                player.playerVelocityY = player.playerAcceleration;
                return 0;
                break;
            case SDLK_SPACE:
                //player.shoot(deltaTime);
                return 0;
                break;
            case SDLK_ESCAPE:
                return 1; // RJP - Shutdown game.
                break;
            case SDLK_RETURN:
                return 2; 
                break;
        }
    }
    else if (event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
        case SDLK_DOWN:
            player.playerVelocityY = 0;
            break;
        case SDLK_RIGHT:
        case SDLK_LEFT:
            player.playerVelocityX = 0;
            break;
        }
    }
    return 0;
}
