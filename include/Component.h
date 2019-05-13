#pragma once

#include <iostream>

#include "GameObject.h"

class GameObject;

class Component
{
  public:
    virtual void Start();
    Component(GameObject &associated);
    virtual ~Component();
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual bool Is(std::string type) = 0;

  protected:
    GameObject &associated;
};