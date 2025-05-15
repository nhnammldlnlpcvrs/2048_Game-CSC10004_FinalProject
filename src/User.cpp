#include "User.h"
#include <fstream>

void User::writeToFile(std::ofstream& out) const {
    size_t len = username.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(username.c_str(), len);

    len = password.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(password.c_str(), len);

    out.write(reinterpret_cast<const char*>(&score), sizeof(score));
}

void User::readFromFile(std::ifstream& in) {
    size_t len = 0;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    username.resize(len);
    in.read(&username[0], len);

    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    password.resize(len);
    in.read(&password[0], len);

    in.read(reinterpret_cast<char*>(&score), sizeof(score));
}
