#pragma once

#include "GameObject.h"
#include "Vec2.h"

class Camera
{
public:
    void Follow (GameObject* newFocus);
    void Unfollow();
    void Update(float dt);
    Vec2 pos;
    Vec2 speed;
private:
    GameObject* focus;
};