#pragma once

#define PENGUINBODY_SPRITE_PATH "assets/img/penguin.png"
#define PENGUIN_ACCELERATION 0.025
#define SPEED_LIM 2.5
#define ANG_SPEED 1
#define PENGUIN_HP 100
#define PENGUIN_DEATH_ANIM_PATH "assets/img/penguindeath.png"
#define PENGUIN_DEATH_ANIM_COUNT 5.0
#define PENGUIN_DEATH_ANIM_TIME 3.0
#define PENGUIN_DEATH_SOUND_PATH "assets/audio/boom.wav"

#include <memory>

#include "Sprite.h"
#include "Component.h"
#include "Vec2.h"
#include "GameObject.h"
#include "Collider.h"
#include "Bullet.h"
#include "Sound.h"

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
    void NotifyCollision(GameObject &other);
    Vec2 Pos();

private:
    std::weak_ptr<GameObject> pcannon;
    Vec2 speed;
    float linearSpeed;
    float angle;
    int hp;
};