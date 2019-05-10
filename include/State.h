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
#include "CameraFollower.h"
#include "Alien.h"

class State
{
public:
  void Start();
  State();
  ~State();
  bool QuitRequested();
  void LoadAssets();
  void Update(float dt);
  void Render();
  std::weak_ptr<GameObject> AddObject(GameObject* go);
  std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);

private:
  Music music;
  bool quitRequested;
  void Input();
  std::vector<std::shared_ptr<GameObject>> objectArray;
  bool started;
};
#endif