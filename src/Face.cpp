#include "../include/Face.h"

Face::Face(GameObject &associated) : Component::Component(associated),
                                     hitpoints(30)
{
}

void Face::Damage(int damage)
{
    hitpoints = hitpoints - damage;
    if (hitpoints <= 0)
    {
        associated.RequestDelete();
        Sound* sound = (Sound *)associated.GetComponent("Sound").get();
        if (sound != nullptr)
        {
        sound->Play();
        }
    }
}

void Face::Update(float dt) {}
void Face::Render() {}

bool Face::Is(std::string type)
{
    if (type == "Face")
    {
        return true;
    }
    else
    {
        return false;
    }
}
