#include "Board.h"
#include "Global.h"
#include <cstdlib>

void setupBoard() {
    board = new int* [4];
    prevBoard = new int* [4];
    for (int i = 0; i < 4; i++) {
        board[i] = new int[4] {};
        prevBoard[i] = new int[4] {};
    }
    randomTile(board, true);
    randomTile(board, true);
}

void updateBoardState() {
    copyBoard(board, prevBoard);
}

void copyBoard(int** src, int** dest) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            dest[i][j] = src[i][j];
}

bool boardsEqual(int** a, int** b) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (a[i][j] != b[i][j]) return false;
    return true;
}

void randomTile(int** board, bool isStart) {
    int empty[16][2];
    int count = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                empty[count][0] = i;
                empty[count][1] = j;
                count++;
            }
        }
    }
    if (count > 0) {
        int r = rand() % count;
        board[empty[r][0]][empty[r][1]] = (rand() % 10 < 9) ? 2 : 4;
    }
}