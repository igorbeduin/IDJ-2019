#include <string>
#include <iostream>
#include "TargetConditionals.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "../include/Game.hpp"

Game::Game (std::string title, int width, int height) {
    int SDL_ERROR;
    int IMG_ERROR;
    int MSC_ERROR;

    if (Game::instance != nullptr) {
        std::cout << "Something's Wrong!";
    } else {
        Game::instance = this;
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
            window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0); // resolver inputs
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
    std::string title = "Igor R. O. Beduin - 14/0143882";
    // dimensoes da janela do jogo
    int width = 1024;
    int height = 600;

    if (Game::instance != nullptr) {
        return *Game::instance;
    } else {
        Game::instance = new Game(title, width, height);
        return *Game::instance;
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
        state->Update(33);
        state->Render();
        SDL_RenderPresent(renderer);
    }
}