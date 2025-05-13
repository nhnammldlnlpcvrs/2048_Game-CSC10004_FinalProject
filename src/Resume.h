#pragma once

#include <string>
#include "User.h"
#include "MatrixStack.h"

// Lưu trạng thái game vào file resume
void saveResume(
    const std::string& filename,
    const User& user,
    matrixStack& undo,
    matrixStack& redo,
    int** matrix,
    int n,
    int goal,
    int undo_redo,
    int speed,
    int countdown
);

// Đọc trạng thái game từ file resume
bool loadResume(
    const std::string& filename,
    User& user,
    matrixStack& undo,
    matrixStack& redo,
    int**& matrix,
    int& n,
    int& goal,
    int& undo_redo,
    int& speed,
    int& countdown
);

// Kiểm tra file resume có tồn tại không
bool hasResume(const std::string& filename);

// Xóa file resume khi không cần dùng nữa
void deleteResume(const std::string& filename);
