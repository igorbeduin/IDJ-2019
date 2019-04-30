#include "../include/InputManager.h"

InputManager &InputManager::GetInstance()
{
    static InputManager instance;
    return instance;
}

InputManager::InputManager() : mouseState{false, false, false, false, false, false},
                               mouseUpdate{0, 0, 0, 0, 0, 0},
                               quitRequested(false),
                               updateCounter(0),
                               mouseX(0),
                               mouseY(0)
{
}

InputManager::~InputManager()
{
}

void InputManager::Update()
{
    SDL_Event event;

    // Atualiza a posição do mouse nos atributos da class
    SDL_GetMouseState(&mouseX, &mouseY);

    // Garante que, se um evento de quit não foi resolvido, o jogo continue rodando sem problemas
    // Ex.: O jogo esteja rodando com a flag de quit setada.
    quitRequested = false;

    // Retorna TRUE se ocorrer eventos e processa a pilha de eventos
    while (SDL_PollEvent(&event))
    {   
        // Garante que o mesmo evento não seja gravado repetidamente
        if (event.key.repeat) 
        {
            break;
        }

        switch (event.type)
        {
        // Evento de tecla pressionada
        case SDL_KEYDOWN:
            /*
                TODO:
                - processamento do evento de teclado usando 
                  unordered map.
            */
            break;

        // Evento de soltura de tecla
        case SDL_KEYUP:
            /*
                TODO:
                - processamento do evento de teclado usando 
                  unordered map.
            */
            break;

        // Evento de pressionamento de botão do mouse
        case SDL_MOUSEBUTTONDOWN:
            // event.button.button guarda o botão que occorreu o evento
            mouseState[event.button.button] = true;
            break;

        // Evento de soltura do botão do mouse
        case SDL_MOUSEBUTTONUP:
            // event.button.button guarda o botão que occorreu o evento
            mouseState[event.button.button] = false;
            break;

        // Evento de QUIT
        case SDL_QUIT:
            quitRequested = true;
            break;
        }
        updateCounter ++;
        // TODO: contador de Updates (mouseUpdate)
    }
}

bool InputManager::QuitRequested()
{
    return quitRequested;
}

int InputManager::GetMouseX()
{
    return mouseX;
}

int InputManager::GetMouseY()
{
    return mouseY;
}
