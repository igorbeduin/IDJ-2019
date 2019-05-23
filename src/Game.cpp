#include "../include/Game.h"
#include "../include/Resources.h"
#include "../include/InputManager.h"

#define AUDIO_CHUNKSIZE 1024
#define AUDIO_FREQUENCY MIX_DEFAULT_FREQUENCY
#define AUDIO_FORMAT MIX_DEFAULT_FORMAT
#define AUDIO_CHANNELS MIX_DEFAULT_CHANNELS
#define SOUND_RESOLUTION 32

#define WINDOW_FLAGS 0 // Ex.: SDL_WINDOW_FULLSCREEN

// Configurações da janela do jogo
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Igor R. O. Beduin - 14/0143882"

// Static class member initialization
Game* Game::instance = nullptr;

Game::Game(std::string title, int width, int height) : frameStart(0),
                                                       storedState(nullptr),
                                                       dt(0.0)
{
    int SDL_ERROR;
    int IMG_ERROR;
    int MSC_ERROR;

    if (Game::instance != nullptr)
    {
        std::cout << "Game: Something's Wrong!";
    }
    else
    {
        Game::instance = this;
    }

    SDL_ERROR = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    if (SDL_ERROR != 0)
    {
        // Garantia de inicialização
        std::cout << "Game: SDL_Init falhou";
    }
    else
    {
        std::cout << "Game: SDL_Init iniciou corretamente" << std::endl;
        IMG_ERROR = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
        if (IMG_ERROR == 0)
        {
            std::cout << "Game: IMG_Init nao carregou nenhum loader";
            // Tratar erro depois
        }
        else
        {
            std::cout << "Game: IMG_Init iniciou corretamente" << std::endl;
            MSC_ERROR = Mix_Init(MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3);
            if (MSC_ERROR == 0)
            {
                std::cout << "Game: Mix_Init nao carregou nenhum loader";
            }
            else
            {
                std::cout << "Game: Mix_Init iniciou corretamente" << std::endl;
                Mix_OpenAudio(AUDIO_FREQUENCY, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_CHUNKSIZE);
                Mix_AllocateChannels(SOUND_RESOLUTION);
                window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, WINDOW_FLAGS);
                if (window == nullptr)
                {
                    std::cout << "Game: Falha na criação da janela" << std::endl;
                }
                else
                {
                    std::cout << "Game: Window criada com sucesso!" << std::endl;
                }
                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
                if (renderer == nullptr)
                {
                    std::cout << "Game: Falha na criação do renderer" << std::endl;
                }
                else
                {
                    std::cout << "Game: Renderer criado com sucesso!" << std::endl;
                }
            }
        }
    } 
}

Game::~Game()
{
    if (storedState != nullptr)
    {
        storedState = nullptr;
    }
    while (!stateStack.empty())
    {
        stateStack.pop();
    }

    Mix_Quit();
    IMG_Quit();
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

Game &Game::GetInstance()
{
    if (Game::instance != nullptr)
    {
        return *Game::instance;
    }
    else
    {
        Game::instance = new Game(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
        return *Game::instance;
    }
}

SDL_Renderer *Game::GetRenderer()
{
    return renderer;
}

State &Game::GetCurrentState()
{
    return *stateStack.top();
}

void Game::Push(State* state)
{
    storedState = state;
}

void Game::Run()
{   
    if (storedState != nullptr)
    {
        storedState->Start();
        stateStack.push((std::unique_ptr<State>)storedState);
        storedState = nullptr;
        while (!stateStack.top()->QuitRequested() && !stateStack.empty())
        {   
            if (stateStack.top()->QuitRequested())
            {
                stateStack.pop();
                if (!stateStack.empty())
                {
                    stateStack.top()->Resume();
                }
            }
            if (storedState != nullptr)
            {
                stateStack.top()->Pause();
                stateStack.push((std::unique_ptr<State>)storedState);
                stateStack.top()->Start();
            }

            CalculateDeltaTime();
            InputManager::GetInstance().Update();
            stateStack.top()->Update(dt);
            stateStack.top()->Render();
            SDL_RenderPresent(Game::GetInstance().GetRenderer());
            Resources::ClearAll();
        }
    }
}

void Game::CalculateDeltaTime()
{
    int instTime = SDL_GetTicks();

    dt = (instTime - frameStart) / 1000.0; // converting time from miliseconds to seconds
    frameStart = instTime;
}

float Game::GetDeltaTime()
{
    return dt;
}