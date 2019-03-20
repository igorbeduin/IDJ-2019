#include <SDL2/SDL.h>

#include "State.hpp"


State::State() {
    quitRequested = false;
    // Instanciar o Sprite
}

void State::LoadAssets() {
    // Preload de música, imagens, etc
}

void State::Update(float dt) {
    if (SDL_QuitRequested == true) {
        quitRequested = true;
    }
}

void State::Render() {
    // Renderizar o fundo "bg"
}

bool QuitRequested() {
    return quitRequested;
}