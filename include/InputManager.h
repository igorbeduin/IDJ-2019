#pragma once

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
    std::unoredered_map<int, int> keyUpdate;
    int mouseX;
    int mouseY;
};