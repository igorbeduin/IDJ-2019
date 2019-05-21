#pragma once

#include <memory>

#include "GameObject.h"

class State
{
public:
    State();
    ~State();
    virtual void LoadAssets() = 0;
    void Update(float dt) = 0;
    void Render() = 0;
    void Start() = 0;
    void Pause() = 0;
    void Resume() = 0;
    std::weak_ptr<GameObject> AddObject(GameObject* object) = 0;
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* object) = 0;
    bool PopRequested();
    bool QuitRequested();

    
protected:
    void virtual StartArray();
    void virtual UpdateArray(float dt);
    void virtual RenderArray();
    bool popRequested;
    bool quitRequested;
    bool started;

    std::vector<std::shared_ptr<GameObject>> objectArray;

};