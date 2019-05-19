#include "../include/GameObject.h"

GameObject::GameObject() : started(false),
                           box(0, 0, 0, 0),
                           angleDeg(0),
                           isDead(false)
{
}

GameObject::GameObject(int startingX, int startingY) : GameObject()
{
    this->box.DefineCenter(Vec2(startingX, startingY));
}

GameObject::GameObject(Vec2 startingPos) : GameObject()
{
    this->box.DefineCenter(startingPos);
}

GameObject::~GameObject()
{

    components.clear();
}

void GameObject::Update(float dt)
{   
    for (int i = components.size() - 1; i >= 0; --i)
    {
        components[i]->Update(dt);
    }
}

void GameObject::Render()
{   
    for (int i = components.size() -1; i >= 0; --i)
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

void GameObject::AddComponent(std::shared_ptr<Component> cpt)
{   
    components.emplace_back(cpt);
    if (started)
    {
        components.back()->Start();
    }
}

void GameObject::RemoveComponent(std::shared_ptr<Component> cpt)
{
    for (int i = components.size() - 1; i >= 0; i--)
    {   
        if (components[i] == cpt)
        {
            components.erase(components.begin()+i);
        }
    }
}

std::shared_ptr<Component> GameObject::GetComponent(std::string type)
{
    for (int i = components.size() - 1; i >= 0; i--)
    {
        if (components[i]->Is(type))
        {
            return components[i];
        }
    }
    return nullptr;
}

void GameObject::Start()
{
    for (int i = 0; i < (int)components.size(); i++)
    {
        components[i]->Start();
    }
        started = true;
}

double GameObject::GetAngleRad()
{
    return angleDeg / (180 / 3.141592);
}

void GameObject::NotifyCollision(GameObject &other)
{
    for (int i = 0; i < (int)components.size(); i++)
    {
        components[i]->NotifyCollision(other);
    }
}
