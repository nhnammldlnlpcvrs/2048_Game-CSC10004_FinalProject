#pragma once
void setupBoard();
void updateBoardState();
bool isWin();
bool isLose();
bool boardsEqual(int** a, int** b);
void copyBoard(int** src, int** dest);
void randomTile(int** board, bool isStart);