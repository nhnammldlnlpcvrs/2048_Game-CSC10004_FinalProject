#include "Sound.h"
#include "Global.h"
#include <SDL_mixer.h>

void toggleMusic() {
    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(gMusic, -1);
    }
    else if (Mix_PausedMusic() == 1) {
        Mix_ResumeMusic();
    }
    else {
        Mix_PauseMusic();
    }
}