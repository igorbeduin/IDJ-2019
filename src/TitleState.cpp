#include "../include/TitleState.h"
#include "../include/Game.h"
#include "../include/InputManager.h"
#include "../include/CameraFollower.h"
#include "../include/Camera.h"


TitleState::TitleState() : State::State()
{
    GameObject *menu = new GameObject();
    Sprite* menuSprite= new Sprite(*menu, TITLE_IMAGE_PATH);
    menu->AddComponent((std::shared_ptr<Component>)menuSprite);
    // CameraFollower* cameraMenu = new CameraFollower(*menu);
    // menu->AddComponent((std::shared_ptr<Component>)cameraMenu);
    AddObject(menu);

    GameObject *title = new GameObject();
    Text *titleText = new Text(*title, TITLE_FONT_PATH, 50, Text::BLENDED, TITLE_PLAY_TEXT, TITLE_FONT_COLOR, 2);
    title->AddComponent((std::shared_ptr<Component>)titleText);
    title->box.DefineCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    AddObject(title);

}

void TitleState::Update(float dt)
{   
    // Camera::Update(dt);
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
