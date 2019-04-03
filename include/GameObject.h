#pragma once

// #ifndef GAME_OBJECT_H
// #define GAME_OBJECT_H

#include <iostream>
#include "Rect.h"
#include "Component.h"
#include <vector>

class Component;

class GameObject
{
  public:
    GameObject();
    ~GameObject();
    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component *cpt);
    void RemoveComponent(Component *cpt);
    Component *GetComponent(std::string type);
    Rect box;

  private:
    std::vector<Component *> components;
    bool isDead;
};