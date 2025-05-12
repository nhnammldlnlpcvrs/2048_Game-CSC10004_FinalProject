#pragma once
#include <vector>

class matrixStack {
private:
    std::vector<int**> data;
    std::vector<int> sizes; // lưu kích thước ma trận tương ứng với từng frame

public:
    matrixStack();
    ~matrixStack();

    void push(int** matrix, int n);    // Lưu ma trận vào stack
    int** pop(int& n);                 // Lấy ma trận ra khỏi stack
    bool isEmpty() const;             // Stack có rỗng không
    void clear();                      // Xoá toàn bộ stack
};
