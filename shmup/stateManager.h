#pragma once
#include "gameState.h"

class StateManager {
public:
    StateManager();

    void setGameState(GameState state);
    GameState getGameState() const;

private:
    GameState currentState;
};