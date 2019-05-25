#include "../include/EndState.h"
#include "../include/GameData.h"
#include "../include/Game.h"
#include "../include/InputManager.h"


EndState::EndState() : State::State()
{   
    GameObject* endScreen = new GameObject();
    GameObject* firstMsg = new GameObject();

    Sprite* endScreenSprite;
    Text* firstMsgText;

    SDL_Color endTextColor;
    std::string conditinalText;
    if (GameData::playerVictory)
    {
        endScreenSprite = new Sprite(*endScreen, WIN_SCREEN_PATH);
        conditinalText = "CONGRATULATIONS!!! You have won!";
        endTextColor = {0, 200, 0, 0}; // Green
    }
    else
    {
        endScreenSprite = new Sprite(*endScreen, LOSE_SCREEN_PATH);
        conditinalText = "Oh no! You have lost!";
        endTextColor = {200, 0, 0, 0}; // Red
    }
    std::string text = conditinalText;
    firstMsgText = new Text(*firstMsg, TITLE_FONT_PATH, 50, Text::BLENDED, text, endTextColor, 2);

    endScreen->AddComponent((std::shared_ptr<Component>)endScreenSprite);
    firstMsg->AddComponent((std::shared_ptr<Component>)firstMsgText);
    firstMsg->box.DefineCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    AddObject(endScreen);
    std::weak_ptr<GameObject> weak_firstMsg = AddObject(firstMsg);

    GameObject* secondMsg = new GameObject();
    Text *secondMsgText = new Text(*secondMsg, TITLE_FONT_PATH, 40, Text::BLENDED, "Press ESC to go to Menu or SPACEBAR to play again", endTextColor, 2);
    secondMsg->AddComponent((std::shared_ptr<Component>)secondMsgText);
    secondMsg->box.DefineCenter(weak_firstMsg.lock()->box.GetCenter() + Vec2(0, 50));
    AddObject(secondMsg);
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