#include "../include/Collider.h"

#ifdef DEBUG
#include "../include/Camera.h"
#include "../include/Game.h"

#include <SDL2/SDL.h>
#endif //DEBUG

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component::Component(associated),
                                                                      scale(scale),
                                                                      offset(offset)
{}

void Collider::Update(float dt)
{
    this->box = associated.box;
    this->box.w = this->box.w * scale.x;
    this->box.h = this->box.h * scale.y;

    this->box.DefineCenter(associated.box.GetCenter() + offset.GetRotatedDeg(associated.angleDeg));

}

void Collider::Render()
{
#ifdef DEBUG
    Vec2 center(box.GetCenter());
    SDL_Point points[5];

    Vec2 point = (Vec2(box.x, box.y) - center).Rotate(associated.angleDeg / (180 / PI)) + center + Camera::pos;
    points[0] = {(int)point.x, (int)point.y};
    points[4] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x + box.w, box.y) - center).Rotate(associated.angleDeg / (180 / PI)) + center + Camera::pos;
    points[1] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x + box.w, box.y + box.h) - center).Rotate(associated.angleDeg / (180 / PI)) + center + Camera::pos;
    points[2] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x, box.y + box.h) - center).Rotate(associated.angleDeg / (180 / PI)) + center + Camera::pos;
    points[3] = {(int)point.x, (int)point.y};

    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}

bool Collider::Is(std::string type)
{
    return (type == "Collider");
}

void Collider::SetScale(Vec2 scale)
{
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset)
{
    this->offset = offset;
}

void Collider::NotifyCollision(GameObject &other)
{}
