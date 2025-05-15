#include "TopPlayer.h"
#include <fstream>
#include <algorithm>

Top20List::Top20List() {
    load();
}

void Top20List::addPlayer(const std::string& name, unsigned int score) {
    players.push_back({ name, score });
    sortDescending();
    if (players.size() > 20)
        players.pop_back();
    save();
}

void Top20List::load() {
    players.clear();
    std::ifstream in(filename, std::ios::binary);
    if (!in) return;

    int count = 0;
    in.read(reinterpret_cast<char*>(&count), sizeof(count));
    for (int i = 0; i < count; ++i) {
        PlayerRecord p;
        int len = 0;
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        p.username.resize(len);
        in.read(&p.username[0], len);
        in.read(reinterpret_cast<char*>(&p.score), sizeof(p.score));
        players.push_back(p);
    }
    in.close();
}

void Top20List::save() {
    std::ofstream out(filename, std::ios::binary);
    size_t count = players.size();
    out.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (auto& p : players) {
        int len = static_cast<int>(p.username.size());
        if (len < 0 || static_cast<size_t>(len) != p.username.size()) {
            throw std::overflow_error("Username size exceeds the range of int.");
        }
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(p.username.c_str(), len);
        out.write(reinterpret_cast<const char*>(&p.score), sizeof(p.score));
    }
    out.close();
}

void Top20List::sortDescending() {
    std::sort(players.begin(), players.end(), [](const PlayerRecord& a, const PlayerRecord& b) {
        return a.score > b.score;
        });
}

std::vector<PlayerRecord> Top20List::getTopPlayers() const {
    return players;
}
