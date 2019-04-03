#include <iostream>
#include "../include/Component.h"

GameObject::GameObject()
{
    isDead = false;
}

GameObject::~GameObject()
{
    for (int i = components.size(); i >= 0; --i)
    {
        delete *(components.begin() + i);
    }
    components.clear();
}

void GameObject::Update(float dt)
{
    for (int i = components.size(); i >= 0; --i)
    {
        components[i]->Update(dt);
    }
}

void GameObject::Render()
{
    for (int i = components.size(); i >= 0; --i)
    {
        components[i]->Render();
    }
}

bool GameObject::IsDead()
{
    return isDead;
}

void GameObject::RequestDelete()
{
    isDead = true;
}

void GameObject::AddComponent(Component *cpt)
{
    components.push_back(cpt);
}

void GameObject::RemoveComponent(Component *cpt)
{
    bool cptFound = false;

    for (int i = components.size(); i >= 0; i--)
    {
        if (components[i] == cpt)
        {
            delete components[i];
            cptFound = true;
        }
    }

    if (cptFound == false)
    {
        std::cout << "No component found!" << std::endl;
    }
}

Component *GameObject::GetComponent(std::string type)
{
    for (int i = components.size(); i >= 0; i--)
    {
        if (components[i]->Is(type))
        {
            return components[i];
        }
    }

    std::cout << "No component found!" << std::endl;
    return nullptr;
}
