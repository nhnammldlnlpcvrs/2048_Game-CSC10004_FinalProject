#include "MatrixStack.h"
#include <fstream>

matrixStack::matrixStack() {
    topIndex = -1;
}

bool matrixStack::isEmpty() const {
    return topIndex == -1;
}

bool matrixStack::isFull() const {
    return topIndex >= MAX_STACK_SIZE - 1;
}

void matrixStack::push(const Matrix& m) {
    if (!isFull()) {
        stack[++topIndex] = m;
    }
}

Matrix matrixStack::pop() {
    if (!isEmpty()) {
        return stack[topIndex--];
    }
    Matrix empty;
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            empty.matrix[i][j] = 0;
    return empty;
}

void matrixStack::clear() {
    topIndex = -1;
}

void matrixStack::writeToFile(std::ofstream& outFile) const {
    outFile.write(reinterpret_cast<const char*>(&topIndex), sizeof(topIndex));
    outFile.write(reinterpret_cast<const char*>(stack), sizeof(Matrix) * (topIndex + 1));
}

void matrixStack::readFromFile(std::ifstream& inFile) {
    inFile.read(reinterpret_cast<char*>(&topIndex), sizeof(topIndex));
    inFile.read(reinterpret_cast<char*>(stack), sizeof(Matrix) * (topIndex + 1));
}
