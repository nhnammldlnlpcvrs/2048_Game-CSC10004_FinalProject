#include "Logic.h"
#include "Global.h"
#include "Board.h"
#include "Sound.h"

bool handleGameEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && !win && !lose) {
        score += scorePerMove;
        scorePerMove = 0;
        switch (e.key.keysym.sym) {
        case SDLK_UP:
            moveUp(board, scorePerMove);
            if (!boardsEqual(board, prevBoard)) randomTile(board, false);
            break;
        case SDLK_DOWN:
            moveDown(board, scorePerMove);
            if (!boardsEqual(board, prevBoard)) randomTile(board, false);
            break;
        case SDLK_LEFT:
            moveLeft(board, scorePerMove);
            if (!boardsEqual(board, prevBoard)) randomTile(board, false);
            break;
        case SDLK_RIGHT:
            moveRight(board, scorePerMove);
            if (!boardsEqual(board, prevBoard)) randomTile(board, false);
            break;
        case SDLK_m:
            toggleMusic();
            break;
        default:
            break;
        }
        return true;
    }
    return false;
}

// Dummy move functions:
void moveLeft(int** board, int& score) {}
void moveRight(int** board, int& score) {}
void moveUp(int** board, int& score) {}
void moveDown(int** board, int& score) {}