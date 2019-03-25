#pragma once

#include <SDL2/SDL.h>
#include "State.hpp"

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
