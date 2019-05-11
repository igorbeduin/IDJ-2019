#include "../include/Minion.h"

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
        radius.x = shared_alien->box.w / 2 * 1.25;
        radius.y = shared_alien->box.h / 2 * 1.25;
    }
    else
    {   
        associated.RequestDelete();
    }
    radius.Rotate(arc);
}

void Minion::Update(float dt)
{
    if (alienCenter.lock().get() != nullptr)
    {
        std::cout << "radius.x: " << radius.x << std::endl;
        std::cout << "radius.y: " << radius.y << std::endl;
        std::cout << "radius.Magnitude(): " << radius.Magnitude() << std::endl;

        radius.Rotate(ARC_STEP/100);

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


