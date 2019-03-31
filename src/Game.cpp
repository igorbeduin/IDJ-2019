#include <string>
#include <iostream>

#include "../include/Game.h"

#define AUDIO_CHUNKSIZE 1024
#define AUDIO_FREQUENCY MIX_DEFAULT_FREQUENCY
#define AUDIO_FORMAT MIX_DEFAULT_FORMAT
#define AUDIO_CHANNELS MIX_DEFAULT_CHANNELS
#define SOUND_RESOLUTION 32

#define WINDOW_FLAGS 0 // Ex.: SDL_WINDOW_FULLSCREEN

// Static class member initialization
Game *Game::instance = nullptr;

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
    if (SDL_ERROR != 0) { 
        // Garantia de inicialização
        std::cout << "SDL_Init falhou";
    } else {
        std::cout << "SDL_Init iniciou corretamente" << std::endl;
        IMG_ERROR = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
        if (IMG_ERROR == 0){
            std::cout << "IMG_Init nao carregou nenhum loader";
            // Tratar erro depois
        } else {
            std::cout << "IMG_Init iniciou corretamente" << std::endl;
            MSC_ERROR = Mix_Init(MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3);
            if (MSC_ERROR == 0) {
                std::cout << "Mix_Init nao carregou nenhum loader";
            } else {
                std::cout << "Mix_Init iniciou corretamente" << std::endl;
                Mix_OpenAudio(AUDIO_FREQUENCY, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_CHUNKSIZE);
                Mix_AllocateChannels(SOUND_RESOLUTION);
                window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, WINDOW_FLAGS);
                if (window == nullptr) {
                    std::cout << "Falha na criação da janela" <<std::endl;
                } else {
                    std::cout << "Window criada com sucesso!" << std::endl;
                }
                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
                if (renderer == nullptr) {
                    std::cout << "Falha na criação do renderer" << std::endl;
                } else {
                    std::cout << "Renderer criado com sucesso!" << std::endl;
                }
            }
        }
    } // End of initialization routine
    state = new State();
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
        SDL_RenderPresent(Game::GetInstance().GetRenderer());
    }
}