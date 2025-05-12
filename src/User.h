#pragma once
#include <string>

struct User {
    std::string username;
    std::string passwordHash;
    unsigned int score;

    User(std::string user = "", std::string pass = "", unsigned int s = 0)
        : username(user), passwordHash(pass), score(s) {
    }
};
