#include "../include/Resources.h"

std::unordered_map<std::string, SDL_Texture *> Resources::imageTable;
std::unordered_map<std::string, Mix_Music *> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk *> Resources::soundTable;
std::unordered_map<std::string, TTF_Font *> Resources::fontTable;

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
    std::cout << "Todos os sons foram apagados!" << std::endl;
}

TTF_Font *Resources::GetFont(std::string file, int fontSize)
{
    std::string key = file + std::to_string(fontSize);

    TTF_Font *font;
    std::unordered_map<std::string, TTF_Font *>::iterator it = Resources::fontTable.find(key);
    if (it == Resources::fontTable.end())
    {
        std::cout << "Resources: No Font found on Table! "
                  << "(" << key << ")" << std::endl;
        std::cout << "Resources: Loading a new file... "
                  << "(" << key << ")" << std::endl;
        font = TTF_OpenFont(file.c_str(), fontSize);
        
        Resources::fontTable.insert({key, font});
        std::cout << "Loading done! "
                  << "(" << file << ")" << std::endl;
        return font;
    }
    return it->second;
}

void Resources::ClearFonts()
{
    int i = 0;
    while (fontTable.begin() != fontTable.end())
    {
        std::cout << "Limpando memória de fontes..."
                  << " (" << i + 1 << ") " << std::endl;
        fontTable.erase(fontTable.begin()++);
        i++;
    }
    std::cout << "Todas as fontes foram apagadas!" << std::endl;
}

void Resources::ClearAll()
{
    ClearImages();
    ClearMusics();
    ClearSounds();
    ClearFonts();
}