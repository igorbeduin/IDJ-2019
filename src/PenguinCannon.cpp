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
    
    // Adicionando Collider
    Collider *penguinCannon_collider = new Collider(associated);
    associated.AddComponent((std::shared_ptr<Collider>)penguinCannon_collider);

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
    shootCooldown.Update(dt);

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
    associated.angleDeg = angle * (180/PI);

    if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON))
    {   
        if (shootCooldown.Get() >= PENGUIN_BULLET_CD)
        {
            Shoot();
            std::cout << "PENGUIN: iiiii pew " << std::endl;
            shootCooldown.Restart();
        }
    }
}

void PenguinCannon::Render()
{}

void PenguinCannon::Shoot()
{
    //Criando a bullet
    Vec2 bulletDistanceFromPeng = Vec2(associated.box.w * BULLET_WIDTH_FACTOR, 0).Rotate(angle);
    GameObject *bullet = new GameObject(associated.box.GetCenter() + bulletDistanceFromPeng);
    Bullet *bullet_behaviour = new Bullet(*bullet, angle, PENGUIN_BULLET_SPEED, PENGUIN_BULLET_DAMAGE, PENGUIN_BULLET_DISTANCE, PENGUIN_BULLET_SPRITE_PATH, "Player");
    bullet->AddComponent((std::shared_ptr<Bullet>)bullet_behaviour);

    std::weak_ptr<GameObject> weak_bullet = Game::GetInstance().GetCurrentState().AddObject(bullet);
    Sprite *bulletSprite = (Sprite *)weak_bullet.lock()->GetComponent("Sprite").get();
    bulletSprite->SetFrameCount(PENGUINCANNON_FRAME_COUNT);
    bulletSprite->SetFrameTime(PENGUINCANNON_FRAME_TIME);
}

bool PenguinCannon::Is(std::string type)
{
    return (type == "PenguinCannon");
}

void PenguinCannon::NotifyCollision(GameObject &other)
{}
