#include "../include/Bullet.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite, std::string shooter) : Component::Component(associated),
                                                                                                                                                    distanceLeft(maxDistance),
                                                                                                                                                    damage(damage),
                                                                                                                                                    shooter(shooter)
{
    // Criando o sprite do tiro
    Sprite *bullet_sprite = new Sprite(associated, sprite);
    associated.AddComponent((std::shared_ptr<Sprite>)bullet_sprite);
    this->speed.x = cos(angle) * speed;
    this->speed.y = sin(angle) * speed;
    associated.angleDeg = this->speed.ArgDeg();

    // Adicionando Collider
    Collider *bullet_collider = new Collider(associated);
    associated.AddComponent((std::shared_ptr<Collider>)bullet_collider);
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

bool Bullet::IsShooter(std::string shooter)
{
    return (shooter == this->shooter);
}

void Bullet::NotifyCollision(GameObject &other)
{
    std::shared_ptr<Component> shared_pengBody = other.GetComponent("PenguinBody");
    std::shared_ptr<Component> shared_Alien = other.GetComponent("Alien");

    // Se a colisão ocorre com o pinguim
    if ((shared_pengBody.get() != nullptr) && (shooter != "Player"))
    {   
        associated.RequestDelete();
    }
    // Se a colisão ocorre com o alien
    if ((shared_Alien.get() != nullptr) && (shooter != "Enemy"))
    {
        associated.RequestDelete();
    }
}
