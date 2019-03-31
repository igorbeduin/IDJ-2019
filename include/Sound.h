#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <iostream>
#include "../include/GameObject.h"

class Sound {
    public:
        Sound(GameObject& associated);
        Sound(GameObject &associated, std:string file);
        ~Sound();
        void Play(int times = 1);
        void Stop();
        void Open(std::string file);
        bool IsOpen();
        void Update(float dt);
        void Render();
        void Is(std::string type);

      private:
        Mix_Chunk* chunk;
        int channel;
}