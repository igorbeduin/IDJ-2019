#include "../include/InputManager.h"

static InputManager instance;

InputManager& InputManager::GetInstance()
{
    return instance;
}

InputManager::InputManager() : quitRequested(false),
                               updateCounter(0)
{
    /*
    TODO:
        Inicializar:
        * mouseState
        * mouseUpdate
    */
}

void InputManager::Update()
{
    /*
    TODO:
        Tratar eventos
    */
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
