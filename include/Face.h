#pragma once

// #ifndef FACE_H
// #define FACE_H

#include <iostream>
#include "GameObject.h"
#include "Component.h"
#include <memory>
#include "Sound.h"

class Face : public Component
{
  public:
    Face(GameObject &associated);
    void Damage(int damage);
    void Update(float dt);
    void Render();
    bool Is(std::string type);

  private:
    int hitpoints;
};