#pragma once

#include "Sprite.hpp"
#include "Music.hpp"

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