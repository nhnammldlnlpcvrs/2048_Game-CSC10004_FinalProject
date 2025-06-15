#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

extern SDL_Renderer* gRenderer;
extern Mix_Music* gMusic;
extern int score, best, scorePerMove;
extern bool win, lose;
extern int** board;
extern int** prevBoard;