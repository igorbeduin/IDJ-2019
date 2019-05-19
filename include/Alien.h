#pragma once

#define ALIEN_SPRITE_PATH "assets/img/alien.png"
#define ALIEN_VELOCITY 300
#define ALIEN_ANG_VEL 8 // degree/frame
#define ALIEN_HP 150
#define ALIEN_DEATH_ANIM_PATH "assets/img/aliendeath.png" 
#define ALIEN_DEATH_ANIM_COUNT 4.0
#define ALIEN_DEATH_ANIM_TIME 3.0
#define ALIEN_DEATH_SOUND_PATH "assets/audio/boom.wav"

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
#include "Collider.h"

    enum ActionType {
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
  void NotifyCollision(GameObject &other);

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