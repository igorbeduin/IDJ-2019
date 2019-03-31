#pragma once

#include "Sprite.h"
#include "Music.h"

class State {
    public:
        State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();

    private:
        Sprite bg;
        Music music;
        bool quitRequested;
};