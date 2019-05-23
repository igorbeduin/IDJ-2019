#include "../include/TitleState.h"
#include "../include/Game.h"
#include "../include/InputManager.h"
#include "../include/CameraFollower.h"
#include "../include/Camera.h"


TitleState::TitleState() : State::State()
{   
    GameObject* title = new GameObject();
    Sprite* titleSprite = new Sprite(*title, TITLE_IMAGE_PATH);
    title->AddComponent((std::shared_ptr<Component>)titleSprite);
    CameraFollower* camera = new CameraFollower(*title);
    title->AddComponent((std::shared_ptr<Component>)camera);
    AddObject(title);
}

void TitleState::Update(float dt)
{   
    Camera::Update(dt);
    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested())
    {
        quitRequested = true;
    }
    if (InputManager::GetInstance().KeyPress(SPACEBAR_KEY))
    {   
        StageState* stage = new StageState();
        Game::GetInstance().Push(stage);
        popRequested = true;
    }
    for (int i = 0; i != (int)objectArray.size(); i++)
    {
        objectArray[i]->Update(dt);
    }
}

void TitleState::LoadAssets()
{}

void TitleState::Render()
{
    for (int i = 0; i != (int)objectArray.size(); i++)
    {
        objectArray[i]->Render();
    }
}

void TitleState::Start()
{
    LoadAssets();
    for (int i = 0; i < (int)objectArray.size(); i++)
    {
        objectArray[i]->Start();
    }
    started = true;
}

void TitleState::Pause()
{}

void TitleState::Resume()
{}
