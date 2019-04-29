#include "../include/InputManager.h"


InputManager& InputManager::GetInstance()
{
    static InputManager instance;
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

InputManager::~InputManager()
{
    
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
