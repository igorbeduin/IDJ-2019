#include "../include/Bullet.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite) : Component::Component(associated),
                                                                                                          distanceLeft(maxDistance),
                                                                                                          damage(damage)
{
    // Criando o sprite do tiro
    Sprite* bullet_sprite = new Sprite(associated, sprite);
    associated.AddComponent((std::shared_ptr<Sprite>)bullet_sprite);
    this->speed.x = cos(angle) * speed;
    this->speed.y = sin(angle) * speed;
}

void Bullet::Update(float dt)
{
    Vec2 step(speed.x * dt, speed.y * dt);
    associated.box.DefineCenter(associated.box.GetCenter() + step);

    distanceLeft -= step.Magnitude();

    if (distanceLeft <= 0)
    {
        associated.RequestDelete();
    }
}

void Bullet::Render()
{}

bool Bullet::Is(std::string type)
{
    return (type == "Bullet");
}

int Bullet::GetDamage()
{
    return damage;
}


