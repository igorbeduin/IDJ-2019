#pragma once

#define INCLUDE_SDL
#include "State.hpp"
#include "SDL_include.h"

class Game {
    private:
        static Game* instance;
        Game(std::string title, int width, int height);
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;

    public:
        ~Game();
        void Run();
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game& GetInstance();
};
