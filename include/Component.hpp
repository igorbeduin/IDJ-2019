#pragma once

#include <string>
#include "../include/GameObject.hpp"

class Component {
    public:
        Component(GameObject& associated);
        virtual ~Component();
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;
        virtual bool Is(std::string type) = 0;

    protected:
        GameObject& associated;
}