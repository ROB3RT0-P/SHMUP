/*******************************************
    Written by Robert Parry [RJP] - 2023
    Refer to main.cpp for the license
*******************************************/

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

class SaveLoad {

    const char* HIGH_SCORE_FILE = "highscore.txt"; // File to store the high score

    bool saveHighScore(int highScore) const {
        FILE* file = fopen(HIGH_SCORE_FILE, "w");
        if (file == NULL) {
            SDL_Log("Failed to open high score file for writing: %s\n", SDL_GetError());
            return false;
        }

        fprintf(file, "%d", highScore);
        fclose(file);
        return true;
    }

    int loadHighScore() {
        int highScore = 0;
        FILE* file = fopen(HIGH_SCORE_FILE, "r");
        if (file != NULL) {
            fscanf(file, "%d", &highScore);
            fclose(file);
        }
        return highScore;
    }
};