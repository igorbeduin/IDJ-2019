#include "../include/Minion.h"
#include "../include/Game.h"

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component::Component(associated),
                                                                                                    alienCenter(alienCenter),
                                                                                                    arc(arcOffsetDeg)
{
    // Adicionando o sprite ao GameObject
    Sprite* minion_sprite = new Sprite(associated, MINION_SPRITE_PATH);
    associated.AddComponent((std::shared_ptr<Sprite>)minion_sprite);

    std::shared_ptr<GameObject> shared_alien = alienCenter.lock();
    if (shared_alien.get() != nullptr)
    {
        // radius inicia com x aproximadamente igual à diagonal do sprite do alien
        radius.x = (shared_alien->box.w / 2);
        radius.y = (shared_alien->box.h / 2);
    }
    else
    {   
        associated.RequestDelete();
    }
    radius.Rotate(arc);
}

void Minion::Update(float dt)
{   
    float arcStep = dt * MINION_ANG_VEL;
    if (alienCenter.lock().get() != nullptr)
    {
        std::cout << "radius.x: " << radius.x << std::endl;
        std::cout << "radius.y: " << radius.y << std::endl;
        std::cout << "radius.Magnitude(): " << radius.Magnitude() << std::endl;

        radius.Rotate(arcStep);

        Vec2 pos = radius + Vec2(alienCenter.lock()->box.x + alienCenter.lock()->box.w / 2, alienCenter.lock()->box.y + alienCenter.lock()->box.h / 2);
        associated.box.DefineCenter(pos.x, pos.y);
    }
    else
    {
        associated.RequestDelete();
    }
}

void Minion::Render()
{}

bool Minion::Is(std::string type)
{
    return (type == "Minion");
}

void Minion::Shoot(Vec2 target)
{
    Vec2 distance = target - Vec2(associated.box.x + (associated.box.w / 2), associated.box.y + (associated.box.h / 2));
    float angle = atan2(distance.y, distance.x);

    // Criando um bullet
    GameObject* bullet = new GameObject();
    Bullet *bullet_behaviour = new Bullet(*bullet, angle, MINION_BULLET_SPEED, MINION_BULLET_DAMAGE, distance.Magnitude(), MINION_BULLET_SPRITE_PATH);
    bullet->AddComponent((std::shared_ptr<Bullet>)bullet_behaviour);

    bullet->box.DefineCenter(associated.box.GetCenter());

    Game::GetInstance().GetState().AddObject(bullet);
}


