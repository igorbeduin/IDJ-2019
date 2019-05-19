#pragma once

#include <iostream>

#include "Sprite.h"
#include "Component.h"
#include "GameObject.h"
#include "math.h"
#include "Vec2.h"
#include "Collider.h"

class Bullet : public Component
{
public:
    Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, std::string sprite, bool originPlayer = false);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    int GetDamage();
    void NotifyCollision(GameObject &other);
    bool FromPlayer();

private:
    Vec2 speed;
    float distanceLeft;
    int damage;
    bool originPlayer;
};