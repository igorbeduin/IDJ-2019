#include "../include/State.h"

State::State() : popRequested(false),
                 quitRequested(false),
                 started(false)
{}

State::~State()
{
    objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject *go)
{
    std::shared_ptr<GameObject> shared_go(go);
    objectArray.push_back(shared_go);
    if (started)
    {
        shared_go->Start();
    }
    std::weak_ptr<GameObject> weak_go(shared_go);
    return weak_go;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *go)
{
    for (int i = 0; i < (int)objectArray.size(); i++)
    {
        if (go == objectArray[i].get())
        {
            std::weak_ptr<GameObject> weak_go(objectArray[i]);
            return weak_go;
        }
    }
    std::weak_ptr<GameObject> empty_weak;
    return empty_weak;
}

void State::Start()
{
}

void State::Pause()
{
}

void State::Resume()
{
}

void State::Update(float dt)
{

}

void State::Render()
{

}
bool State::PopRequested()
{
    return popRequested;
}

bool State::QuitRequested()
{
    return quitRequested;
}

void State::StartArray()
{
    for (int i = 0; i < (int)objectArray.size(); i++)
    {
        objectArray[i]->Start();
    }
}

void State::UpdateArray(float dt)
{
    for (int i = 0; i < (int)objectArray.size(); i++)
    {
        objectArray[i]->Update(dt);
    }
}

void State::RenderArray()
{
    for (int i = 0; i < (int)objectArray.size(); i++)
    {
        objectArray[i]->Render();
    }
}