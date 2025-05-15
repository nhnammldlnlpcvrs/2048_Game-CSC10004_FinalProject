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
    std::stack<MatrixWithScore> data; 

public:
    void push(const Matrix& matrix, int score);
    bool isEmpty() const;
    MatrixWithScore pop();

    void writeToFile(std::ofstream& out) const; // Add 'const' to match the definition
    void readFromFile(std::ifstream& in);
};

#endif
