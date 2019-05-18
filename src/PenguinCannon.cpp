#include "../include/PenguinCannon.h"
#include "../include/InputManager.h"
#include "../include/Game.h"

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> pbody) : Component::Component(associated),
                                                                                             pbody(pbody),
                                                                                             angle(0)
{
    // Criando a sprite
    Sprite* pengCannon_sprite = new Sprite(associated, PENGUINCANNON_SPRITE_PATH);
    associated.AddComponent((std::shared_ptr<Sprite>)pengCannon_sprite);

    std::shared_ptr<GameObject> shared_body = pbody.lock();
    if (shared_body.get() != nullptr)
    {
        associated.box.DefineCenter(shared_body.get()->box.GetCenter());
    }
    else
    {   
        associated.RequestDelete();
    }
}

void PenguinCannon::Update(float dt)
{
    std::shared_ptr<GameObject> shared_body = pbody.lock();
    if (shared_body.get() != nullptr)
    {
        associated.box.DefineCenter(shared_body.get()->box.GetCenter());
    }
    else
    {
        associated.RequestDelete();
    }
    Vec2 mousePos = Vec2(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY());

    angle = Vec2::Distance(associated.box.GetCenter(), mousePos).Arg();
    associated.angleDeg = angle * (180/3.1415);

    if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON))
    {   
        Shoot();
    }
}

void PenguinCannon::Render()
{}

void PenguinCannon::Shoot()
{
    Vec2 mousePos = Vec2(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY());
    Vec2 distanceToTarget = Vec2::Distance(associated.box.GetCenter(), mousePos);
    //Criando a bullet
    GameObject *bullet = new GameObject(associated.box.GetCenter());
    Bullet *bullet_behaviour = new Bullet(*bullet, angle, PENGUIN_BULLET_SPEED, PENGUIN_BULLET_DAMAGE, distanceToTarget.Magnitude(), PENGUIN_BULLET_SPRITE_PATH);
    bullet->AddComponent((std::shared_ptr<Bullet>)bullet_behaviour);

    Game::GetInstance().GetState().AddObject(bullet);
}

bool PenguinCannon::Is(std::string type)
{
    return (type == "PenguinCannon");
}