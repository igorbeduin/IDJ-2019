#pragma once

#include <vector>
#include <memory>

#include "State.h"
#include "Music.h"
#include "TileSet.h"

class StageState : public State
{
public:
  StageState();
  ~StageState();
  void LoadAssets();
  void Update(float dt);
  void Render();
  void Start();
  void Pause();
  void Resume();

private:
  TileSet* tileSet;
  Music backgroundMusic;
};