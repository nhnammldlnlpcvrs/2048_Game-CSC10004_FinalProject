#include "Global.h"

SDL_Renderer* gRenderer = nullptr;
Mix_Music* gMusic = nullptr;
int score = 0, best = 0, scorePerMove = 0;
bool win = false, lose = false;
int** board = nullptr;
int** prevBoard = nullptr;