#pragma once

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include <iostream>
#include <unordered_map>

class Resources
{   
  public:
    SDL_Texture *GetImage(std::string file);
    void ClearImages();
    Mix_Music *GetMusic(std::string file);
    void ClearMusics();
    Mix_Chunk *GetSound(std::string file);
    void ClearSounds();

  private:
    std::unordered_map<std::string, SDL_Texture*> imageTable;
    std::unordered_map<std::string, Mix_Music*> musicTable;
    std::unordered_map<std::string, Mix_Chunk*> soundTable;
};
