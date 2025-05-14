#ifndef USER_H
#define USER_H

#include <string>
#include <fstream>

class User {
private:
    std::string username;
    std::string password; // hoặc passwordHash
    int score;

public:
    User() : username(""), password(""), score(0) {}

    void writeToFile(std::ofstream& out) const;
    void readFromFile(std::ifstream& in);

    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    int getScore() const { return score; }

    void setUsername(const std::string& u) { username = u; }
    void setPassword(const std::string& p) { password = p; }
    void setScore(int s) { score = s; }
};

#endif
