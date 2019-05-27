#ifndef RESOURCES_H
#define RESOURCES_H
#pragma once

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include <iostream>
#include <unordered_map>
#include <string>

#include "SDL_include.h"
#include "Game.h"

class Resources
{   
  public:
    static SDL_Texture *GetImage(std::string file);
    static void ClearImages();
    static Mix_Music *GetMusic(std::string file);
    static void ClearMusics();
    static Mix_Chunk *GetSound(std::string file);
    static void ClearSounds();
    static TTF_Font *GetFont(std::string file, int fontSize);
    static void ClearFonts();

    static void ClearAll();

  private:
    static std::unordered_map<std::string, SDL_Texture*> imageTable;
    static std::unordered_map<std::string, Mix_Music*> musicTable;
    static std::unordered_map<std::string, Mix_Chunk*> soundTable;
    static std::unordered_map<std::string, TTF_Font *> fontTable;
};
#endif