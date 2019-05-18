#include "../include/Minion.h"
#include "../include/Game.h"

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component::Component(associated),
                                                                                                    alienCenter(alienCenter),
                                                                                                    arc(arcOffsetDeg)
{
    // Criando o sprite do Minion
    Sprite* minion_sprite = new Sprite(associated, MINION_SPRITE_PATH);
    // Escala aleatória
    float scale = 1 + ((rand() % 50) / 100.0);
    minion_sprite->SetScale(scale, scale);
    // Adicionando o sprite ao GameObject
    associated.AddComponent((std::shared_ptr<Sprite>)minion_sprite);

    std::shared_ptr<GameObject> shared_alien = alienCenter.lock();
    if (shared_alien.get() != nullptr)
    {
        // Radius inicia com x aproximadamente igual à diagonal do sprite do alien
        radius.x = (shared_alien->box.w / 2);
        radius.y = (shared_alien->box.h / 2);
    }
    else
    {   
        associated.RequestDelete();
    }
    radius.RotateDeg(arc);
    
    // Compensação do giro inicial
    associated.angleDeg -= radius.ArgDeg();


}

void Minion::Update(float dt)
{   
    float arcStep = dt * MINION_ANG_VEL;

    // Compensação de giro
    associated.angleDeg += arcStep;
    if (alienCenter.lock().get() != nullptr)
    {
        radius.RotateDeg(arcStep);
        Vec2 pos = radius + alienCenter.lock().get()->box.GetCenter();
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
    // A Bullet inicia com posição inicial igual a posição do Minion
    GameObject* bullet = new GameObject(associated.box.GetCenter());
    Bullet *bullet_behaviour = new Bullet(*bullet, angle, MINION_BULLET_SPEED, MINION_BULLET_DAMAGE, distance.Magnitude(), MINION_BULLET_SPRITE_PATH);
    bullet->AddComponent((std::shared_ptr<Bullet>)bullet_behaviour);

    std::weak_ptr<GameObject> weak_bullet = Game::GetInstance().GetState().AddObject(bullet);
    Sprite* bulletSprite = (Sprite*)weak_bullet.lock()->GetComponent("Sprite").get();
    bulletSprite->SetFrameCount(MINION_BULLET_FRAME_COUNT);
    bulletSprite->SetFrameTime(MINION_BULLET_FRAME_TIME);
}


