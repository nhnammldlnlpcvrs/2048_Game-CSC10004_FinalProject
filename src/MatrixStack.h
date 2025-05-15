#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H

#include <stack>
#include <fstream>
#include "Matrix.h"

struct MatrixWithScore {
    Matrix matrix;
    int score;
};

class matrixStack {
private:
    std::stack<MatrixWithScore> data; // sửa tên từ `stack` tránh trùng std::stack

public:
    void push(const Matrix& matrix, int score);
    bool isEmpty() const;
    MatrixWithScore pop();

    void writeToFile(std::ofstream& out);
    void readFromFile(std::ifstream& in);
};

#endif
