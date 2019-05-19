#include "../include/PenguinBody.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject &associated) : Component::Component(associated),
                                                   speed(0, 0),
                                                   linearSpeed(0),
                                                   angle(0),
                                                   hp(50)
{
    player = this;
    // Criando a sprite
    Sprite* pengBody_sprite = new Sprite(associated, PENGUINBODY_SPRITE_PATH);
    associated.AddComponent((std::shared_ptr<Sprite>)pengBody_sprite);
    Camera::Follow(&associated);

    // Adicionando Collider
    Collider *penguinBody_collider = new Collider(associated);
    associated.AddComponent((std::shared_ptr<Collider>)penguinBody_collider);
}

PenguinBody::~PenguinBody()
{
    player = nullptr;
    Camera::Unfollow();
}

void PenguinBody::Update(float dt)
{
    if (InputManager::GetInstance().IsKeyDown(W_KEY))
    {
        if (linearSpeed < SPEED_LIM)
        {
            linearSpeed += PENGUIN_ACCELERATION;
        }
    }
    if (InputManager::GetInstance().IsKeyDown(S_KEY))
    {
        if (linearSpeed > -SPEED_LIM)
        {
            linearSpeed -= PENGUIN_ACCELERATION;
        }
    }

    if (InputManager::GetInstance().IsKeyDown(A_KEY))
    {
        associated.angleDeg -= ANG_SPEED;
    }
    if (InputManager::GetInstance().IsKeyDown(D_KEY))
    {
        associated.angleDeg += ANG_SPEED;
    }

    float angleRad = associated.angleDeg / (180 / 3.14159265359);
    Vec2 desloc = Vec2(cos(angleRad) * linearSpeed, sin(angleRad) * linearSpeed);
    associated.box.DefineCenter(associated.box.GetCenter() + desloc);
}

void PenguinBody::Render()
{}

bool PenguinBody::Is(std::string type)
{
    return (type == "PenguinBody");
}

void PenguinBody::Start()
{}

void PenguinBody::NotifyCollision(GameObject &other)
{}
