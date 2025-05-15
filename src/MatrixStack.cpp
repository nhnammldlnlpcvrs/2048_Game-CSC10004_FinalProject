#include "MatrixStack.h"

// Thêm một bản sao ma trận và điểm vào stack
void matrixStack::push(const Matrix& matrix, int score) {
    MatrixWithScore item = { matrix, score }; // Initialize with provided values
    data.push(item);
}

// Trả về true nếu stack trống
bool matrixStack::isEmpty() const {
    return data.empty();
}

// Lấy phần tử đầu và xóa khỏi stack
MatrixWithScore matrixStack::pop() {
    if (data.empty()) {
        // Trả về một giá trị mặc định nếu stack rỗng
        return MatrixWithScore{ {}, 0 };
    }
    MatrixWithScore top = data.top();
    data.pop();
    return top;
}

// Ghi toàn bộ stack vào file (từ top đến bottom)
void matrixStack::writeToFile(std::ofstream& out) const { // Made const
    std::stack<MatrixWithScore> temp = data;

    int size = (int)temp.size();
    out.write(reinterpret_cast<char*>(&size), sizeof(int));

    while (!temp.empty()) {
        MatrixWithScore item = temp.top();
        temp.pop();
        out.write(reinterpret_cast<char*>(&item.matrix), sizeof(Matrix));
        out.write(reinterpret_cast<char*>(&item.score), sizeof(int));
    }
}

// Đọc toàn bộ stack từ file (và phục hồi lại đúng thứ tự)
void matrixStack::readFromFile(std::ifstream& in) {
    MatrixWithScore item = { {}, 0 }; // Initialize with default values
    int size = 0;
    in.read(reinterpret_cast<char*>(&size), sizeof(int));

    std::stack<MatrixWithScore> temp;

    for (int i = 0; i < size; ++i) {
        MatrixWithScore item = { {}, 0 }; // Ensure item is initialized
        in.read(reinterpret_cast<char*>(&item.matrix), sizeof(Matrix));
        in.read(reinterpret_cast<char*>(&item.score), sizeof(int));
        temp.push(item);
    }

    // Reverse the stack to restore the correct order (bottom -> top)
    while (!temp.empty()) {
        data.push(temp.top());
        temp.pop();
    }
}
