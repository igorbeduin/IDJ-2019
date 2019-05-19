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
    
    // Adicionando Collider
    Collider* minion_collider = new Collider(associated);
    associated.AddComponent((std::shared_ptr<Collider>)minion_collider);

    std::shared_ptr<GameObject> shared_alien = alienCenter.lock();
    if (shared_alien.get() != nullptr)
    {
        // Radius inicia com x aproximadamente igual à diagonal do sprite do alien
        radius.x = (shared_alien->box.w);
        radius.y = (shared_alien->box.h);
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
    Vec2 distance = Vec2::Distance(associated.box.GetCenter(), target);
    float angle = atan2(distance.y, distance.x);

    // Criando um bullet
    GameObject *bullet = new GameObject(associated.box.GetCenter());
    Bullet *bullet_behaviour = new Bullet(*bullet, angle, MINION_BULLET_SPEED, MINION_BULLET_DAMAGE, MINION_BULLET_DISTANCE, MINION_BULLET_SPRITE_PATH, "Enemy");
    bullet->AddComponent((std::shared_ptr<Bullet>)bullet_behaviour);
    
    std::weak_ptr<GameObject> weak_bullet = Game::GetInstance().GetState().AddObject(bullet);
    Sprite* bulletSprite = (Sprite*)weak_bullet.lock()->GetComponent("Sprite").get();
    bulletSprite->SetFrameCount(MINION_BULLET_FRAME_COUNT);
    bulletSprite->SetFrameTime(MINION_BULLET_FRAME_TIME);
}

void Minion::NotifyCollision(GameObject &other)
{}
