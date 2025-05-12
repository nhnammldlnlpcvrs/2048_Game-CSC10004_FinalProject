#ifndef GAME_FUNCTION_H
#define GAME_FUNCTION_H

#include <vector>
#include <string>
#include <mutex>
#include "MatrixStack.h"
#include "User.h"
#include "Time.h"
#include "TopPlayer.h"

extern std::mutex m;

void makeMatrix(int**& matrix, int n);
void freeMatrix(int** matrix, int n);

bool processLeft(int** matrix, int n, unsigned int& score);
bool processRight(int** matrix, int n, unsigned int& score);
bool processUp(int** matrix, int n, unsigned int& score);
bool processDown(int** matrix, int n, unsigned int& score);

void randomItem(int** matrix, int n);

bool checkGOV(int** matrix, int n); // Game Over
bool checkWin(int** matrix, int n, int goal);

void saveAccount(
    std::string fileName,
    User user,
    matrixStack& undo,
    matrixStack& redo,
    int** matrix,
    int n,
    int goal,
    int undo_redo,
    int speed,
    int countdown
);

void readAccount(
    std::string fileName,
    User& user,
    matrixStack& undo,
    matrixStack& redo,
    int**& matrix,
    int& n,
    int& goal,
    int& undo_redo,
    int& speed,
    int& countdown
);

void processUndo(
    int xo, int yo,
    int** matrix,
    int n,
    int undo_redo,
    matrixStack& undo,
    matrixStack& redo,
    User& user,
    Time time,
    int goal,
    Top20List list
);

void processRedo(
    int xo, int yo,
    int** matrix,
    int n,
    int undo_redo,
    matrixStack& undo,
    matrixStack& redo,
    User& user,
    Time time,
    int goal,
    Top20List list
);

bool processExit(
    User user,
    matrixStack& undo,
    matrixStack& redo,
    int** matrix,
    int n,
    int goal,
    int undo_redo,
    int speed,
    int countdown,
    Top20List& list
);

#endif // GAME_FUNCTION_H
