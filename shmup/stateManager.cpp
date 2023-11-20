#include "stateManager.h"

StateManager::StateManager() : currentState(GameState::START) {}

void StateManager::setGameState(GameState state) {
    currentState = state;
}

GameState StateManager::getGameState() const {
    return currentState;
}
