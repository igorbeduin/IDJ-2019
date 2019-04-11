#include "../include/Music.h"
#include "../include/Resources.h"

Music::Music(){
    music = nullptr;
}

Music::Music(std::string file)
{
    Open(file);
}

Music::~Music() 
{

}

void Music::Play(int times) {
    if (music != nullptr) {
        Mix_PlayMusic(music, times);
    } else {
        std::cout << "Music: Não existe música como atributo na classe";
    }
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file) {
    
    music = Resources::GetMusic(file.c_str());
    // music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        std::cout << "Music: Falha ao carregar a música!" << std::endl;
    } else {
        std::cout << "Music: Musica carregada com sucesso!" << std::endl;
    }
}

bool Music::IsOpen() {
    if (music != nullptr) {
        return true;
    } else {
        return false;
    }
}
