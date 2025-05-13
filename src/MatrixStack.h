#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H

#include <fstream>

struct Matrix {
    int n;
    int** matrix;
};

class matrixStack {
private:
    static const int MAX_SIZE = 100;
    Matrix stack[MAX_SIZE];   // Mảng lưu các ma trận
    int topIndex;             // Vị trí trên cùng của stack

public:
    matrixStack();  // constructor
    ~matrixStack(); // destructor

    bool isEmpty() const;
    bool isFull() const;
    void push(const Matrix& m);
    Matrix pop();
    Matrix top() const;
    void clear();

    // Hàm ghi/đọc từ file
    void writeToFile(std::ofstream& out) const;
    void readFromFile(std::ifstream& in);
};

#endif
