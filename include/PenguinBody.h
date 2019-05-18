#pragma once

#define PENGUINBODY_SPRITE_PATH "assets/img/penguin.png"
#define PENGUIN_ACCELERATION 0.025
#define SPEED_LIM 2.5
#define ANG_SPEED 1

#include <memory>

#include "Sprite.h"
#include "Component.h"
#include "Vec2.h"
#include "GameObject.h"

class PenguinBody : public Component
{
public:
    PenguinBody(GameObject& associated);
    ~PenguinBody();
    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    static PenguinBody* player;

private:
    std::weak_ptr<GameObject> pcannon;
    Vec2 speed;
    float linearSpeed;
    float angle;
    int hp;
};