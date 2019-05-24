#pragma once

#define WIN_SCREEN_PATH "assets/img/win.jpg"
#define LOSE_SCREEN_PATH "assets/img/lose.jpg"
#define TITLE_FONT_PATH "assets/font/Call me maybe.ttf"

#include "State.h"
#include "Music.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Text.h"
#include "TitleState.h"
#include "StageState.h"

class EndState : public State
{
public:
    EndState();
    // ~EndState();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
private:
    Music backgroundMusic;
};