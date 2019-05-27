#pragma once

#include "State.h"
#include "Music.h"

class EndState : public State
{
public:
    EndState();
    ~EndState();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
private:
    Music backgroundMusic;
};