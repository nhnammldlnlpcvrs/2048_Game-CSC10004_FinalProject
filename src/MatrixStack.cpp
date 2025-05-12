#include "MatrixStack.h"
#include <cstring>

matrixStack::matrixStack() {}

matrixStack::~matrixStack() {
    clear();
}

void matrixStack::push(int** matrix, int n) {
    // Cấp phát và sao chép ma trận
    int** newMatrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        newMatrix[i] = new int[n];
        for (int j = 0; j < n; ++j)
            newMatrix[i][j] = matrix[i][j];
    }
    data.push_back(newMatrix);
    sizes.push_back(n);
}

int** matrixStack::pop(int& n) {
    if (data.empty()) {
        n = 0;
        return nullptr;
    }

    int** topMatrix = data.back();
    n = sizes.back();
    data.pop_back();
    sizes.pop_back();
    return topMatrix;
}

bool matrixStack::isEmpty() const {
    return data.empty();
}

void matrixStack::clear() {
    for (size_t k = 0; k < data.size(); ++k) {
        int** matrix = data[k];
        int size = sizes[k];
        for (int i = 0; i < size; ++i)
            delete[] matrix[i];
        delete[] matrix;
    }
    data.clear();
    sizes.clear();
}
