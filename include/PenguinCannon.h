#pragma once

#define PENGUINCANNON_SPRITE_PATH "assets/img/cubngun.png"
#define PENGUIN_BULLET_SPEED 50.0
#define PENGUIN_BULLET_DAMAGE 30.0
#define PENGUIN_BULLET_SPRITE_PATH "assets/img/penguinbullet.png"

#include <iostream>
#include <memory>

#include "Sprite.h"
#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Bullet.h"

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