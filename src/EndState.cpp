#include "../include/EndState.h"
#include "../include/GameData.h"
#include "../include/Game.h"
#include "../include/InputManager.h"


EndState::EndState() : State::State()
{   
    GameObject* endScreen = new GameObject();
    GameObject* endMessage = new GameObject();

    Sprite* endScreenSprite;
    Text* endMessageText;

    SDL_Color endTextColor;
    std::string conditinalText;
    if (GameData::playerVictory)
    {
        endScreenSprite = new Sprite(*endScreen, WIN_SCREEN_PATH);
        conditinalText = "YES! You have won!";
        endTextColor = {0, 200, 0, 0};
    }
    else
    {
        endScreenSprite = new Sprite(*endScreen, LOSE_SCREEN_PATH);
        conditinalText = "Oh no! You have lost!";
        endTextColor = {200, 0, 0, 0};
    }
    std::string text = conditinalText + "\n" + "Press ESC to go to Menu or SPACEBAR to play again";
    endMessageText = new Text(*endMessage, TITLE_FONT_PATH, 50, Text::BLENDED, text, endTextColor, 2);

    endScreen->AddComponent((std::shared_ptr<Component>)endScreenSprite);
    endMessage->AddComponent((std::shared_ptr<Component>)endMessageText);

    AddObject(endScreen);
    AddObject(endMessage);

}

void EndState::LoadAssets()
{}
void EndState::Update(float dt)
{
    if (InputManager::GetInstance().QuitRequested())
    {
        quitRequested = true;
    }
    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY))
    {
        TitleState* title = new TitleState();
        Game::GetInstance().Push(title);
        popRequested = true;
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
void EndState::Render()
{
    for (int i = 0; i != (int)objectArray.size(); i++)
    {
        objectArray[i]->Render();
    }
}

void EndState::Start()
{
    LoadAssets();
    for (int i = 0; i < (int)objectArray.size(); i++)
    {
        objectArray[i]->Start();
    }
    started = true;
}
void EndState::Pause()
{}
void EndState::Resume()
{}