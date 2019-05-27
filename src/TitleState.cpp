#include "../include/TitleState.h"
#include "../include/InputManager.h"



TitleState::TitleState() : State::State()
{

}

void TitleState::Update(float dt)
{
    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY))
    {
        quitRequested = true;
    }
}

void TitleState::LoadAssets()
{}

void TitleState::Render()
{

}

void TitleState::Start()
{

}

void TitleState::Pause()
{}

void TitleState::Resume()
{}
