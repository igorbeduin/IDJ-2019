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
