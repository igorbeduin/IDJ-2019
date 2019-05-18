#pragma once

#define MINION_SPRITE_PATH "assets/img/minion.png"
#define MINION_ANG_VEL -50
#define MINION_BULLET_SPEED 100.0
#define MINION_BULLET_DAMAGE 30.0
#define MINION_BULLET_SPRITE_PATH "assets/img/minionbullet2.png"
#define MINION_BULLET_FRAME_COUNT 3
#define MINION_BULLET_FRAME_TIME 0.1

#include <iostream>
#include <memory>
#include <math.h>

#include "Sprite.h"
#include "GameObject.h"
#include "Component.h"
#include "Vec2.h"
#include "Bullet.h"

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