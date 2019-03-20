#include <string>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "Game.hpp"

Game::Game (std::string title, int width, int height) {
    int SDL_ERROR;
    int IMG_ERROR;

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
            // Não existe essa função
            window = SDL_CreateWindow(const char* title, int x, int y, int w, int h, Uint32 flags); // resolver inputs
            renderer = SDL_CreateRenderer(SDL_Window* window, int index, Uint32 flags); // resolver inputs
        }
        state = new State;
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
        instance = new Game;
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