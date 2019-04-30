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

    //Atualiza o updateCounter
    updateCounter ++;

    // Retorna TRUE se ocorrer eventos e processa a pilha de eventos
    while (SDL_PollEvent(&event))
    {   
        // Garante que o mesmo evento não seja gravado repetidamente
        if (event.key.repeat != true) 
        {   
            // Switch que lida com os tipos de evento
            switch (event.type)
            {
            // Evento de tecla pressionada
            case SDL_KEYDOWN:
                // event.key.keysym.sym guarda a tecla em que ocorreu o evento
                keyState[event.key.keysym.sym] = true;
                keyUpdate[event.key.keysym.sym] = updateCounter;
                break;

            // Evento de soltura de tecla
            case SDL_KEYUP:
                // event.key.keysym.sym guarda a tecla em que ocorreu o evento
                keyState[event.key.keysym.sym] = false;
                keyUpdate[event.key.keysym.sym] = updateCounter;
                break;

            // Evento de pressionamento de botão do mouse
            case SDL_MOUSEBUTTONDOWN:
                // event.button.button guarda o botão do mouse em que ocorreu o evento
                mouseState[event.button.button] = true;
                mouseUpdate[event.button.button] = updateCounter;
                break;

            // Evento de soltura do botão do mouse
            case SDL_MOUSEBUTTONUP:
                // event.button.button guarda o botão do mouse em que ocorreu o evento
                mouseState[event.button.button] = false;
                mouseUpdate[event.button.button] = updateCounter;
                break;

            // Evento de QUIT
            case SDL_QUIT:
                quitRequested = true;
                break;
            }
        }
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

bool InputManager::KeyPress(int key)
{ 
    // TODO: Metodo que retorna se a tecla esta pressionada naquele instante (frame)
}

bool InputManager::KeyRelease(int key)
{
    // TODO: Metodo que retorna se a tecla esta solta naquele instante (frame)
}

bool InputManager::IsKeyDown(int key)
{ 
    // TODO: Metodo que retorna se a tecla esta pressionada independente de quando o evento inicial ocorreu
}

bool InputManager::MousePress(int button)
{
    // TODO: Metodo que retorna se o botão do mouse esta pressionado naquele instante (frame)
}

bool InputManager::MouseRelease(int button)
{
    // TODO: Metodo que retorna se o botão do mouse esta solto naquele instante (frame)
}

bool InputManager::IsMouseDown(int button)
{
    // TODO: Metodo que retorna se o botão do mouse esta pressionado independente de quando o evento inicial ocorreu
}