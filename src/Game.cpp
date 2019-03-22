#include <string>
#include <iostream>
#include <SDL2/SDL_image.h>
#include < SDL2/SDL_mixer.h>
#include "Game.hpp"

Game::Game (std::string title, int width, int height) {
    int SDL_ERROR;
    int IMG_ERROR;
    int MSC_ERROR;

    if (instance != nullptr) {
        std::cout << "Something's Wrong!";
    } else {
        instance = this;
    }

    SDL_ERROR = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    if (SDL_ERROR != 0) { // Garantia de inicialização
    } else {
        IMG_ERROR = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
        if (IMG_ERROR == 0){
            std::cout << "IMG_Init nao carregou nenhum loader";
            // Tratar erro depois
        } else {
            MSC_ERROR = Mix_Init(MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3);
            Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024); // tratar erro
            Mix_AllocateChannels(32);
            window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0); // resolver inputs
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE); // resolver inputs
        }
        state = new State();
    }
}

Game::~Game() {
    Mix_Quit();
    IMG_Quit();
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

Game& Game::GetInstance() {
    if (instance != nullptr) {
        return *instance;
    } else {
        instance = new Game();
        return *instance;
    }
}

State& Game::GetState () {
    return *state;
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

void Game::Run() {
    while (state->QuitRequested()!=true) {
        state->Update();
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(FRAME_RATE);
    }
}