#include <SDL2/SDL.h>
#include "../include/State.hpp"


State::State() {
    quitRequested = false;
    bg = Sprite("assets/img/ocean.jpg");
}

void State::LoadAssets() {
    // Pre load dos assets
}

void State::Update(float dt) {
    if (SDL_QuitRequested() == true) {
        quitRequested = true;
    }
    SDL_Delay(dt);
}

void State::Render() {
    bg.Render(0, 0);
}

bool State::QuitRequested() {
    return quitRequested;
}