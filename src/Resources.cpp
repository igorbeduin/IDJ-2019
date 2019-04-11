#include "../include/Resources.h"

std::unordered_map<std::string, SDL_Texture *> Resources::imageTable;
std::unordered_map<std::string, Mix_Music *> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk *> Resources::soundTable;

SDL_Texture *Resources::GetImage(std::string file)
{   
    SDL_Texture* texture;
    std::unordered_map<std::string, SDL_Texture*>::iterator it = Resources::imageTable.find(file);
    if (it == Resources::imageTable.end())
    {   
        // std::cout << (*it) << std::endl;
        std::cout << "Resources: No image found on Table! " << "(" << file << ")"  << std::endl;
        std::cout << "Resources: Loading a new file... " << "(" << file << ")" << std::endl;
        texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
        Resources::imageTable.insert({file, texture});
        std::cout << "Loading done! " << "(" << file << ")" << std::endl;
        return texture;
    }
    
    else
    {
        return it->second;
    }
    
}

void Resources::ClearImages()
{   
    int i = 0;
    while (imageTable.begin() != imageTable.end())
    {
        std::cout << "Limpando memória de imagens..." << " (" << i + 1 << ") " << std::endl;
        imageTable.erase(imageTable.begin()++);
        i++;
    }
    std::cout << "Todas as imagens foram apagadas!" << std::endl;
}

Mix_Music *Resources::GetMusic(std::string file)
{
    Mix_Music *music;
    std::unordered_map<std::string, Mix_Music *>::iterator it = Resources::musicTable.find(file);
    if (it == Resources::musicTable.end())
    {
        std::cout << "Resources: No music found on Table! "
                  << "(" << file << ")" << std::endl;
        std::cout << "Resources: Loading a new file... "
                  << "(" << file << ")" << std::endl;
        music = Mix_LoadMUS(file.c_str());
        Resources::musicTable.insert({file, music});
        std::cout << "Loading done! "
                  << "(" << file << ")" << std::endl;
        return music;
    }
    return it->second;
}
    
void Resources::ClearMusics()
{
    int i = 0;
    while (musicTable.begin() != musicTable.end())
    {
        std::cout << "Limpando memória de músicas..."
                  << " (" << i + 1 << ") " << std::endl;
        musicTable.erase(musicTable.begin()++);
        i++;
    }
    std::cout << "Todas as músicas foram apagadas!" << std::endl;
}

Mix_Chunk *Resources::GetSound(std::string file)
{
    Mix_Chunk *chunk;
    std::unordered_map<std::string, Mix_Chunk *>::iterator it = Resources::soundTable.find(file);
    if (it == Resources::soundTable.end())
    {
        std::cout << "Resources: No Sound found on Table! "
                  << "(" << file << ")" << std::endl;
        std::cout << "Resources: Loading a new file... "
                  << "(" << file << ")" << std::endl;
        chunk = Mix_LoadWAV(file.c_str());
        Resources::soundTable.insert({file, chunk});
        std::cout << "Loading done! "
                  << "(" << file << ")" << std::endl;
        return chunk;
    }
    return it->second;
}

void Resources::ClearSounds()
{
    int i = 0;
    while (soundTable.begin() != soundTable.end())
    {
        std::cout << "Limpando memória de sons..."
                  << " (" << i + 1 << ") " << std::endl;
        soundTable.erase(soundTable.begin()++);
        i++;
    }
    std::cout << "Todos os sons foram apagadas!" << std::endl;
}