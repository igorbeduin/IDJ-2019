#include <SDL2/SDL.h>
#include "../include/State.hpp"

#define BACKGROUND_SPRITE_PATH "assets/img/ocean.jpg"
#define BACKGROUND_MUSIC_PATH "assets/audio/stageState.ogg"
#define BACKGROUND_MUSIC_LOOP_TIMES -1 // -1 for infinite loop

State::State() {
    quitRequested = false;
    LoadAssets();
    music.Play(BACKGROUND_MUSIC_LOOP_TIMES);
}

void State::LoadAssets() {
    bg = Sprite(BACKGROUND_SPRITE_PATH);
    music = Music(BACKGROUND_MUSIC_PATH);
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