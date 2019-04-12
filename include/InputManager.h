#pragma once

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_EY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT

#include <unordered_map>

class InputManager
{
public:
    void Update();
    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);
    int GetMouseX();
    int GetMouseY();
    bool QuitRequested();
    static InputManager &GetInstance();

private:
    InputManager();
    ~InputManager();
    bool mouseState[6];
    int mouseUpdate[6];
    std::unordered_map<int, bool> keyState;
    std::unordered_map<int, int> keyUpdate;
    bool quitRequested;
    int updateCounter;
    int mouseX;
    int mouseY;
};