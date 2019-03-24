#include <iostream>
#include "../include/Music.hpp"
#include <SDL2/SDL_mixer.h>
#include "TargetConditionals.h"


Music::Music() {
    music = nullptr;
}

Music::Music(std::string file) {
    Open(file);
}

void Music::Play(int times) {
    if (music != nullptr) {
        Mix_PlayMusic(music, times);
    } else {
        std::cout << "Não existe música como atributo na classe";
    }
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file) {
    Mix_LoadMUS(file.c_str()); // tratar erro
}

bool Music::IsOpen() {
    if (music != nullptr) {
        return true;
    } else {
        return false;
    }
}

Music::~Music() {
    if (music != nullptr) {
        Stop(1500);
        Mix_FreeMusic(music);
    }
}
