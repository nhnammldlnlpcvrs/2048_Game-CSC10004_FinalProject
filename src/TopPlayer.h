#pragma once
#include "User.h"
#include <vector>
#include <string>

struct PlayerRecord {
    std::string username;
    unsigned int score = 0;

    PlayerRecord() : username(""), score(0) {}
    PlayerRecord(const std::string& user, unsigned int scr) : username(user), score(scr) {}
};

class Top20List {
private:
    std::vector<PlayerRecord> players;
    const std::string filename = "leaderboard.dat";

public:
    Top20List();
    void addPlayer(const std::string& name, unsigned int score);
    void load();
    void save();
    void sortDescending();
    std::vector<PlayerRecord> getTopPlayers() const;
};
