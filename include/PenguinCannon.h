#pragma once

#include <iostream>
#include <memory>

#include "Component.h"
#include "GameObject.h"

class PenguinCannon : public Component
{
public:
    PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Shoot();
private:
    std::weak_ptr<GameObject> pbody;
    float angle;
};