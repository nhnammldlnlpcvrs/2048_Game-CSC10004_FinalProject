#ifndef AUDIO_H
#define AUDIO_H

#include <SFML/Audio.hpp>
#include <map>
#include <string>

void loadSounds();
void playSound(const std::string& name);
void stopSound(const std::string& name);
void stopAllSounds();

#endif // AUDIO_H
