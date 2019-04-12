#ifndef GAME_H
#define GAME_H
#pragma once

#define INCLUDE_SDL

#include <string>
#include <iostream>
#include <memory>

#include "SDL_include.h"
#include "State.h"

class State;

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
#endif