#include "GameFunction.h"
#include <iostream>
#include <fstream>

using namespace std;

extern mutex m;

void makeMatrix(int**& matrix, int n) {
    matrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
        for (int j = 0; j < n; ++j)
            matrix[i][j] = 0;
    }
}

void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; ++i)
        delete[] matrix[i];
    delete[] matrix;
}

bool compressLeft(int** matrix, int n, unsigned int& score) {
    bool moved = false;
    for (int i = 0; i < n; ++i) {
        int* newRow = new int[n]();
        int pos = 0;

        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] != 0) {
                newRow[pos++] = matrix[i][j];
            }
        }

        for (int j = 0; j < n - 1; ++j) {
            if (newRow[j] != 0 && newRow[j] == newRow[j + 1]) {
                newRow[j] *= 2;
                score += newRow[j];
                newRow[j + 1] = 0;
                j++;
            }
        }

        int* merged = new int[n]();
        pos = 0;
        for (int j = 0; j < n; ++j)
            if (newRow[j] != 0)
                merged[pos++] = newRow[j];

        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] != merged[j]) {
                moved = true;
                matrix[i][j] = merged[j];
            }
        }

        delete[] newRow;
        delete[] merged;
    }
    return moved;
}

bool rotateMatrix(int**& matrix, int n) {
    int** temp = new int* [n];
    for (int i = 0; i < n; ++i)
        temp[i] = new int[n];

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            temp[i][j] = matrix[n - j - 1][i];

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            matrix[i][j] = temp[i][j];

    for (int i = 0; i < n; ++i)
        delete[] temp[i];
    delete[] temp;

    return true;
}

bool processLeft(int** matrix, int n, unsigned int& score) {
    return compressLeft(matrix, n, score);
}

bool processRight(int** matrix, int n, unsigned int& score) {
    rotateMatrix(matrix, n); rotateMatrix(matrix, n);
    bool moved = compressLeft(matrix, n, score);
    rotateMatrix(matrix, n); rotateMatrix(matrix, n);
    return moved;
}

bool processUp(int** matrix, int n, unsigned int& score) {
    rotateMatrix(matrix, n);
    rotateMatrix(matrix, n);
    rotateMatrix(matrix, n);
    bool moved = compressLeft(matrix, n, score);
    rotateMatrix(matrix, n);
    return moved;
}

bool processDown(int** matrix, int n, unsigned int& score) {
    rotateMatrix(matrix, n);
    bool moved = compressLeft(matrix, n, score);
    rotateMatrix(matrix, n); rotateMatrix(matrix, n); rotateMatrix(matrix, n);
    return moved;
}

void randomItem(int** matrix, int n) {
    vector<pair<int, int>> empty;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (matrix[i][j] == 0)
                empty.push_back({ i, j });

    if (!empty.empty()) {
        int idx = rand() % empty.size();
        int x = empty[idx].first;
        int y = empty[idx].second;
        matrix[x][y] = (rand() % 10 < 9) ? 2 : 4;
    }
}

bool checkGOV(int** matrix, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (matrix[i][j] == 0)
                return false;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n - 1; ++j)
            if (matrix[i][j] == matrix[i][j + 1])
                return false;

    for (int j = 0; j < n; ++j)
        for (int i = 0; i < n - 1; ++i)
            if (matrix[i][j] == matrix[i + 1][j])
                return false;

    return true;
}

bool checkWin(int** matrix, int n, int goal) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (matrix[i][j] >= goal)
                return true;
    return false;
}

void saveAccount(string fileName, User user, matrixStack& undo, matrixStack& redo, int** matrix, int n, int goal, int undo_redo, int speed, int countdown) {
    ofstream out(fileName, ios::binary);
    if (!out) return;

    // Ghi thông tin user
    size_t nameLen = user.getUsername().length();
    size_t passLen = user.getPassword().length();

    out.write(reinterpret_cast<char*>(&nameLen), sizeof(size_t));
    out.write(user.getUsername().c_str(), nameLen);

    out.write(reinterpret_cast<char*>(&passLen), sizeof(size_t));
    out.write(user.getPassword().c_str(), passLen);

    int score = user.getScore();
    out.write(reinterpret_cast<char*>(&score), sizeof(int));

    // Ghi thông tin cấu hình trò chơi
    out.write(reinterpret_cast<char*>(&n), sizeof(n));
    out.write(reinterpret_cast<char*>(&goal), sizeof(goal));
    out.write(reinterpret_cast<char*>(&undo_redo), sizeof(undo_redo));
    out.write(reinterpret_cast<char*>(&speed), sizeof(speed));
    out.write(reinterpret_cast<char*>(&countdown), sizeof(countdown));

    // Lưu stack undo
    undo.writeToFile(out);

    // Lưu ma trận hiện tại
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            out.write(reinterpret_cast<char*>(&matrix[i][j]), sizeof(int));

    out.close();
}

void readAccount(string fileName, User& user, matrixStack& undo, matrixStack& redo, int**& matrix, int& n, int& goal, int& undo_redo, int& speed, int& countdown) {
    ifstream in(fileName, ios::binary);
    if (!in) return;

    // Đọc username
    size_t nameLen, passLen;
    in.read(reinterpret_cast<char*>(&nameLen), sizeof(size_t));
    string username(nameLen, ' ');
    in.read(&username[0], nameLen);

    // Đọc password
    in.read(reinterpret_cast<char*>(&passLen), sizeof(size_t));
    string password(passLen, ' ');
    in.read(&password[0], passLen);

    // Gán lại cho user
    user.setUsername(username);
    user.setPassword(password);

    int score;
    in.read(reinterpret_cast<char*>(&score), sizeof(int));
    user.setScore(score);

    // Đọc thông tin game
    in.read(reinterpret_cast<char*>(&n), sizeof(n));
    in.read(reinterpret_cast<char*>(&goal), sizeof(goal));
    in.read(reinterpret_cast<char*>(&undo_redo), sizeof(undo_redo));
    in.read(reinterpret_cast<char*>(&speed), sizeof(speed));
    in.read(reinterpret_cast<char*>(&countdown), sizeof(countdown));

    // Tạo lại ma trận
    makeMatrix(matrix, n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            in.read(reinterpret_cast<char*>(&matrix[i][j]), sizeof(int));

    // Đọc lại undo stack
    undo.readFromFile(in);

    in.close();
}


void processUndo(int xo, int yo, int**& matrix, int& n, int undo_redo, matrixStack& undo, matrixStack& redo, User& user, Time time, int goal, Top20List list) {
    if (!undo.isEmpty()) {
        redo.push(matrix, n);
        Matrix prev = undo.pop();
        freeMatrix(matrix, n);
        n = prev.n;
        matrix = prev.matrix;
    }
}

void processRedo(int xo, int yo, int**& matrix, int& n, int undo_redo, matrixStack& undo, matrixStack& redo, User& user, Time time, int goal, Top20List list) {
    if (!redo.isEmpty()) {
        undo.push(matrix, n);
        Matrix next = redo.pop();
        freeMatrix(matrix, n);
        n = next.n;
        matrix = next.matrix;
    }
}


bool processExit(User user, matrixStack& undo, matrixStack& redo, int** matrix, int n, int goal, int undo_redo, int speed, int countdown, Top20List& list) {
    m.lock();
    saveAccount("resume.dat", user, undo, redo, matrix, n, goal, undo_redo, speed, countdown);
    m.unlock();
    list.addPlayer(user.username, user.score);
    return true;
}
