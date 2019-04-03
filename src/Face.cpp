#include "../include/Face.h"

Face::Face(GameObject &associated) : Component::Component(associated),
                                     hitpoints(30)
{
}

void Face::Damage(int damage)
{
    Component* sound;
    hitpoints = hitpoints - damage;
    if (hitpoints <= 0)
    {
        associated.RequestDelete();
        sound = associated.GetComponent("Sound");
        if (sound != nullptr)
        {
        // sound->Sound::Play();
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
