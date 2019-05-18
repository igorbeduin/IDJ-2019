#pragma once

#define ALIEN_SPRITE_PATH "assets/img/alien.png"
#define ALIEN_VELOCITY 300
#define ALIEN_ANG_VEL 8 // degree/frame

#include <iostream>
#include <queue>
#include <math.h>
#include <limits>

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Minion.h"
#include "Rect.h"
#include "State.h"

enum ActionType
{
  MOVE,
  SHOOT
};

class Alien : public Component
{
public:
  Alien(GameObject &associated, int nMinions);
  ~Alien();
  void Start();
  void Update(float dt);
  void Render();
  bool Is(std::string type);

private:
  class Action
  {
  public:
    Action(ActionType type, float x, float y);
    ActionType type;
    Vec2 pos;
  };
  Vec2 speed;
  int hp;
  std::queue<Action> taskQueue;
  std::vector<std::weak_ptr<GameObject>> minionArray;
  int nMinions;
};