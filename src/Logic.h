#pragma once
bool handleGameEvent(SDL_Event& e);
void moveLeft(int** board, int& score);
void moveRight(int** board, int& score);
void moveUp(int** board, int& score);
void moveDown(int** board, int& score);