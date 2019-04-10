#pragma once

#include <vector>
#include <memory>

#include "Sprite.h"
#include "Sound.h"
#include "GameObject.h"
#include "TileMap.h"
#include "TileSet.h"

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
    GameObject background;
    TileSet *tileSet;
    Sprite *bg_sprite;
    Sound *bg_sound;
    TileMap *bg_tileMap; 
    bool quitRequested;
    void Input();
    void AddObject(int mouseX, int mouseY);
    std::vector<std::shared_ptr<GameObject>> objectArray;
};