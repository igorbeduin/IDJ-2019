#ifndef STATE_H
#define STATE_H
#pragma once

#include <vector>
#include <memory>

#include "Sprite.h"
#include "Music.h"
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
  Music music;
  bool quitRequested;
  void Input();
  void AddObject(int mouseX, int mouseY);
  std::vector<std::shared_ptr<GameObject>> objectArray;
};
#endif