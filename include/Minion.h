#pragma once

#define MINION_SPRITE_PATH "assets/img/minion.png"
#define ARC_STEP -3.14159265359 / 5

#include <iostream>
#include <memory>
#include <math.h>

#include "Sprite.h"
#include "GameObject.h"
#include "Component.h"
#include "Vec2.h"

class Minion : public Component
{
public:
    Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Shoot(Vec2 target);

private:
    Vec2 radius;
    std::weak_ptr<GameObject> alienCenter;
    float arc;
};