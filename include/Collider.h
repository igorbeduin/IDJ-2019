#pragma once

//#define DEBUG

#include <iostream>

#include "Component.h"
#include "Vec2.h"
#include "Rect.h"
#include "GameObject.h"

class Collider : public Component
{
public:
    Collider(GameObject& associated, Vec2 scale = {1, 1},
                                     Vec2 offset = {0, 0});
    Rect box;
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void SetScale(Vec2 scale);
    void SetOffset(Vec2 offset);
    void NotifyCollision(GameObject &other);

private:
    Vec2 scale;
    Vec2 offset;
};