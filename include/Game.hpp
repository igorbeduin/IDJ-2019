#pragma once

#include <SDL2/SDL.h>
#include "State.hpp"

#define FRAME_RATE 33 //ms


class Game {
    private:
        Game(std::string title, int width, int height);
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;

    public:
        ~Game();
        static Game& GetInstance();
        void Run();
        SDL_Renderer* GetRenderer();
        State& GetState();
};
