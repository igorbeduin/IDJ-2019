#include "../include/Game.h"
#include "../include/Resources.h"
#include "../include/InputManager.h"

// Static class member initialization
Game *Game::instance = nullptr;

Game::Game(std::string title, int width, int height) : storedState(nullptr),
                                                       frameStart(0),
                                                       dt(0.0)
{
    int SDL_ERROR;
    int IMG_ERROR;
    int MSC_ERROR;
    int TTF_ERROR;

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
                TTF_ERROR = TTF_Init();
                if (TTF_ERROR != 0)
                {
                    std::cout << "Game: Falha na inicialização do TTF" << std::endl;
                }
                else
                {
                    std::cout << "Game: TTF iniciado com sucesso!" << std::endl;
                    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, WINDOW_FLAG);
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
    TTF_Quit();
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

void Game::Push(State *state)
{
    storedState = state;
}

void Game::Run()
{
    if (storedState != nullptr)
    {
        stateStack.push((std::unique_ptr<State>)storedState);
        stateStack.top()->Start();
        storedState = nullptr;
    }

    // GameLoop
    while (!stateStack.empty())
    {
        if (stateStack.top()->QuitRequested())
        {
            break;
        }
        if (stateStack.top()->PopRequested())
        {
            stateStack.top()->Pause();
            stateStack.pop();
            if (!stateStack.empty())
            {
                stateStack.top()->Resume();
            }
        }
        if (storedState != nullptr)
        {
            if (!stateStack.empty())
            {
                stateStack.top()->Pause();
            }
            stateStack.push((std::unique_ptr<State>)storedState);
            stateStack.top()->Start();
            storedState = nullptr;
        }

        CalculateDeltaTime();
        InputManager::GetInstance().Update();
        stateStack.top()->Update(dt);
        stateStack.top()->Render();
        SDL_RenderPresent(Game::GetInstance().GetRenderer());
    }

    Resources::ClearAll();
    
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