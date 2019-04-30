#include "../include/Face.h"
#include "../include/InputManager.h"

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

void Face::Update(float dt)
{
    if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON))
    {
        if (associated.box.Contains(InputManager::GetInstance().GetMouseX(),
                                    InputManager::GetInstance().GetMouseY()))
        {
            int damage = std::rand() % 10 + 10;
            std::cout << "Damage applied: " << damage << std::endl;
            // Aplica dano
            Damage(damage);
                                    }
    }
}
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
