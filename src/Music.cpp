#include <iostream>
#include "../include/Music.hpp"
#include <SDL2/SDL_mixer.h>


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
    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        std::cout << "Falha ao carregar a música!" << std::endl;
    } else {
        std::cout << "Musica carregada com sucesso!" << std::endl;
    }
}

bool Music::IsOpen() {
    if (music != nullptr) {
        return true;
    } else {
        return false;
    }
}

Music::~Music() {
    // # DESTRUCTOR sendo chamado logo depois da instanciacao da music
    // if (music != nullptr) {
    //     Stop(1500);
    //     Mix_FreeMusic(music);
    // }
}
