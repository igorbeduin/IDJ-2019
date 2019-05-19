#pragma once

#define PENGUINCANNON_SPRITE_PATH "assets/img/cubngun.png"
#define PENGUIN_BULLET_SPEED 100.0
#define PENGUIN_BULLET_DAMAGE 30.0
#define PENGUIN_BULLET_SPRITE_PATH "assets/img/penguinbullet.png"
#define PENGUINCANNON_FRAME_COUNT 4
#define PENGUINCANNON_FRAME_TIME 2
#define BULLET_WIDTH_FACTOR 0.75
#define PENGUIN_BULLET_CD 0.25

#include <iostream>
#include <memory>

#include "Sprite.h"
#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Bullet.h"
#include "Collider.h"
#include "Timer.h"

class PenguinCannon : public Component
{
public:
    PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Shoot();
    void NotifyCollision(GameObject &other);

private:
    std::weak_ptr<GameObject> pbody;
    float angle;
    Timer shootCooldown;
};