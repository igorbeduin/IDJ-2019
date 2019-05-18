#pragma once

#define BULLET_FRAME_COUNT 4
#define BULLET_FRAME_TIME 1

#include <iostream>

#include "Sprite.h"
#include "Component.h"
#include "GameObject.h"
#include "math.h"
#include "Vec2.h"

class Bullet : public Component
{
public:
    Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, std::string sprite);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    int GetDamage();

private:
    Vec2 speed;
    float distanceLeft;
    int damage;
};