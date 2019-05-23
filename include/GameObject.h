#pragma once

#ifndef PI
#define PI 3.1415
#endif

#include <iostream>
#include <vector>
#include <string>

#include "Rect.h"
#include "Component.h"

class Component;

class GameObject
{
public:
  void Start();
  bool started;
  GameObject();
  GameObject(int startingX, int startingY);
  GameObject(Vec2 startingPos);
  ~GameObject();
  void Update(float dt);
  void Render();
  bool IsDead();
  void RequestDelete();
  void AddComponent(std::shared_ptr<Component> cpt);
  void RemoveComponent(std::shared_ptr<Component> cpt);
  double GetAngleRad();
  std::shared_ptr<Component> GetComponent(std::string type);
  Rect box;
  double angleDeg;
  void NotifyCollision(GameObject& other);

private:
  std::vector<std::shared_ptr<Component>> components;
  bool isDead;
};