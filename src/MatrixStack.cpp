#include "MatrixStack.h"
#include <iostream>

matrixStack::matrixStack() : topIndex(-1) {
    // Constructor khởi tạo topIndex về -1 (stack rỗng)
}

matrixStack::~matrixStack() {
    // Destructor giải phóng bộ nhớ cho các ma trận
    clear();
}

bool matrixStack::isEmpty() const {
    return topIndex == -1; // Kiểm tra nếu stack rỗng
}

bool matrixStack::isFull() const {
    return topIndex == MAX_SIZE - 1; // Kiểm tra nếu stack đầy
}

void matrixStack::push(const Matrix& m) {
    if (isFull()) {
        std::cerr << "Stack is full! Cannot push new matrix." << std::endl;
        return;
    }
    stack[++topIndex] = m; // Thêm ma trận vào stack
}

Matrix matrixStack::pop() {
    if (isEmpty()) {
        std::cerr << "Stack is empty! Cannot pop matrix." << std::endl;
        // Trả về một ma trận trống nếu stack rỗng
        Matrix emptyMatrix = { 0, nullptr };
        return emptyMatrix;
    }
    return stack[topIndex--]; // Lấy ma trận ra và giảm topIndex
}

Matrix matrixStack::top() const {
    if (isEmpty()) {
        std::cerr << "Stack is empty! Cannot retrieve top matrix." << std::endl;
        // Trả về một ma trận trống nếu stack rỗng
        Matrix emptyMatrix = { 0, nullptr };
        return emptyMatrix;
    }
    return stack[topIndex]; // Trả về ma trận trên cùng mà không xóa
}

void matrixStack::clear() {
    for (int i = 0; i <= topIndex; ++i) {
        // Giải phóng bộ nhớ cho ma trận đã lưu trong stack
        if (stack[i].matrix != nullptr) {
            for (int j = 0; j < stack[i].n; ++j) {
                delete[] stack[i].matrix[j];
            }
            delete[] stack[i].matrix;
        }
    }
    topIndex = -1; // Đặt lại stack về trạng thái rỗng
}

void matrixStack::writeToFile(std::ofstream& out) const {
    out << topIndex + 1 << std::endl; // Ghi số lượng ma trận trong stack
    for (int i = 0; i <= topIndex; ++i) {
        out << stack[i].n << std::endl; // Ghi kích thước ma trận
        for (int j = 0; j < stack[i].n; ++j) {
            for (int k = 0; k < stack[i].n; ++k) {
                out << stack[i].matrix[j][k] << " "; // Ghi các phần tử của ma trận
            }
            out << std::endl;
        }
    }
}

void matrixStack::readFromFile(std::ifstream& in) {
    clear(); // Xóa stack hiện tại trước khi đọc từ file
    int numMatrices;
    in >> numMatrices; // Đọc số lượng ma trận từ file
    for (int i = 0; i < numMatrices; ++i) {
        Matrix m;
        in >> m.n; // Đọc kích thước ma trận
        m.matrix = new int* [m.n];
        for (int j = 0; j < m.n; ++j) {
            m.matrix[j] = new int[m.n];
            for (int k = 0; k < m.n; ++k) {
                in >> m.matrix[j][k]; // Đọc các phần tử của ma trận
            }
        }
        push(m); // Đưa ma trận vào stack
    }
}
