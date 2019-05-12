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
    associated.box.DefineCenter(associated.box.x + (associated.box.w / 2) + step.x,
                                associated.box.y + (associated.box.h / 2) + step.y);

    distanceLeft -= step.Magnitude();
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


