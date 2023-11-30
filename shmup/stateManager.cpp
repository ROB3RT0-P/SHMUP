/*******************************************
    Written by Robert Parry [RJP] - 2023
*******************************************/

// RJP - I may switch over to using this later.

#include "stateManager.h"

StateManager::StateManager() : currentState(GameState::START) {}

void StateManager::setGameState(GameState state) {
    currentState = state;
}

GameState StateManager::getGameState() const {
    return currentState;
}
