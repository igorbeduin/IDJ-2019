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
    void AddComponent(std::shared_ptr<Component> cpt);
    void RemoveComponent(std::shared_ptr<Component> cpt);
    std::shared_ptr<Component> GetComponent(std::string type);
    Rect box;
  private:
    std::vector<std::shared_ptr<Component>> components;
    bool isDead;
};