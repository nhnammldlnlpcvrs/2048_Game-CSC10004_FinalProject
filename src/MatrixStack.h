#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H
#include "Matrix.h"    // Cần để dùng struct Matrix
#include <fstream>      // Cần để dùng ofstream / ifstream

const int MAX_STACK_SIZE = 100;

class matrixStack {
private:
    Matrix stack[MAX_STACK_SIZE];
    int topIndex;

public:
    matrixStack();                      // Constructor

    bool isEmpty() const;              // Kiểm tra rỗng
    bool isFull() const;               // Kiểm tra đầy

    void push(const Matrix& m);        // Đẩy ma trận vào stack
    Matrix pop();                      // Lấy ma trận ra khỏi stack
    void clear();                      // Xóa toàn bộ stack

    void writeToFile(std::ofstream& outFile) const;   // Ghi stack vào file
    void readFromFile(std::ifstream& inFile);         // Đọc stack từ file
};

#endif
