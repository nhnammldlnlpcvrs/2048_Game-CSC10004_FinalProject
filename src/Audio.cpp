#include "Audio.h"
#include <iostream>

// Map chứa các hiệu ứng âm thanh đã load
std::map<std::string, sf::SoundBuffer> soundBuffers;
std::map<std::string, sf::Sound> sounds;

void loadSounds() {
    std::vector<std::string> soundNames = {
        "move",       // khi di chuyển ô
        "merge",      // khi gộp ô
        "win",        // khi thắng
        "lose",       // khi thua
        "navigate",   // khi di chuyển menu
        "select"      // khi chọn menu
    };

    for (const auto& name : soundNames) {
        sf::SoundBuffer buffer;
        std::string path = "assets/sounds/move.wav";
        if (!buffer.loadFromFile(path)) {
            std::cerr << "Failed to load sound: " << path << std::endl;
            continue;
        }

        soundBuffers[name] = buffer;
        sounds[name].setBuffer(soundBuffers[name]);
    }
}

void playSound(const std::string& name) {
    if (sounds.find(name) != sounds.end()) {
        sounds[name].play();
    }
    else {
        std::cerr << "Sound not found: " << name << std::endl;
    }
}

void stopSound(const std::string& name) {
    if (sounds.find(name) != sounds.end()) {
        sounds[name].stop();
    }
}

void stopAllSounds() {
    for (auto& [name, sound] : sounds) {
        sound.stop();
    }
}
