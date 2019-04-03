#pragma once

// #ifndef STATE_H
// #define STATE_H

#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"
#include <vector>
#include <memory>

class State
{
  public:
    State();
    ~State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();

  private:
    Sprite bg;
    Music music;
    bool quitRequested;
    void Input();
    void AddObject(int mouseX, int mouseY);
    std::vector<std::unique_ptr<GameObject>> objectArray;
};