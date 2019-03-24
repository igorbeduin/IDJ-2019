#pragma once

#include <iostream>
#include "TargetConditionals.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class Music {
    public:
        Music();
        Music(std::string file);
        void Play(int times = -1);
        void Stop(int msToStop = 1500);
        void Open(std::string file);
        bool IsOpen();
        ~Music();
    private:
        Mix_Music* music;
};