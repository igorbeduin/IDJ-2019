#pragma once

#define INCLUDE_SDL
#define INCLUDE_SDL_TTF

#include <string>
#include <iostream>
#include <memory>
#include <stack>

#include "SDL_include.h"
#include "State.h"

class State;

class Game
{
public:
    Game(std::string title, int width, int height);
    ~Game();
    static Game& GetInstance();
    SDL_Renderer *GetRenderer();
    State& GetCurrentState();
    void Push(State* state);
    void Run();
    float GetDeltaTime();

private:
    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* storedState;
    int frameStart;
    float dt;
    void CalculateDeltaTime();
    std::stack<std::unique_ptr<State>> stateStack;
};