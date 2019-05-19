#pragma once

#define INCLUDE_SDL

#include <iostream>
#include <memory>

#include "GameObject.h"
#include "Component.h"
#include "Sound.h"

class Face : public Component
{
  public:
    Face(GameObject &associated);
    void Damage(int damage);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void NotifyCollision(GameObject &other);

  private:
    int hitpoints;
};