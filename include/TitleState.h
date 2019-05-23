#pragma once

#define TITLE_IMAGE_PATH "assets/img/title.jpg"

#include "State.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Component.h"
#include "StageState.h"

class TitleState : public State
{
public:
    TitleState();
    // ~TitleState();
    void LoadAssets();
    void Update(float dt);
    void Render();
    void Start();
    void Pause();
    void Resume();
};