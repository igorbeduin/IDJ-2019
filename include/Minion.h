#pragma once

#define MINION_SPRITE_PATH "assets/img/minion.png"
#define MINION_ANG_VEL -50
#define MINION_BULLET_SPEED 300.0
#define MINION_BULLET_DAMAGE 30.0
#define MINION_BULLET_SPRITE_PATH "assets/img/minionbullet2.png"
#define MINION_BULLET_FRAME_COUNT 3
#define MINION_BULLET_FRAME_TIME 0.1
#define MINION_BULLET_DISTANCE 2000

#ifndef PI
#define PI 3.1415
#endif

#include <iostream>
#include <memory>
#include <math.h>

#include "Alien.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Component.h"
#include "Vec2.h"
#include "Bullet.h"
#include "Collider.h"
#include "Sound.h"

class Minion : public Component
{
public:
    Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Shoot(Vec2 target);
    void NotifyCollision(GameObject &other);

private:
    Vec2 radius;
    std::weak_ptr<GameObject> alienCenter;
    float arc;
};