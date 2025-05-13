#include "Resume.h"
#include <fstream>
#include <iostream>

void saveResume(const std::string& filename, const User& user, matrixStack& undo, matrixStack& redo, int** matrix, int n, int goal, int undo_redo, int speed, int countdown) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) return;

    user.writeToFile(outFile);

    outFile.write((char*)&n, sizeof(int));
    outFile.write((char*)&goal, sizeof(int));
    outFile.write((char*)&undo_redo, sizeof(int));
    outFile.write((char*)&speed, sizeof(int));
    outFile.write((char*)&countdown, sizeof(int));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            outFile.write((char*)&matrix[i][j], sizeof(int));

    undo.writeToFile(outFile);
    redo.writeToFile(outFile);

    outFile.close();
}

bool loadResume(const std::string& filename, User& user, matrixStack& undo, matrixStack& redo, int**& matrix, int& n, int& goal, int& undo_redo, int& speed, int& countdown) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) return false;

    user.readFromFile(inFile);

    inFile.read((char*)&n, sizeof(int));
    inFile.read((char*)&goal, sizeof(int));
    inFile.read((char*)&undo_redo, sizeof(int));
    inFile.read((char*)&speed, sizeof(int));
    inFile.read((char*)&countdown, sizeof(int));

    matrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            inFile.read((char*)&matrix[i][j], sizeof(int));
        }
    }

    undo.readFromFile(inFile);
    redo.readFromFile(inFile);

    inFile.close();
    return true;
}

bool hasResume(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    return inFile.good();
}

void deleteResume(const std::string& filename) {
    std::remove(filename.c_str());
}
