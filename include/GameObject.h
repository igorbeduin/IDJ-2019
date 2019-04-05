#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Rect.h"
#include "Component.h"

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
    void AddComponent(Component * cpt);
    void RemoveComponent(Component * cpt);
    Component * GetComponent(std::string type);
    Rect box;
    int ComponentsSize();
  private:
    std::vector<Component *> components;
    bool isDead;
};