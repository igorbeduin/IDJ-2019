#include <iostream>
#include "../include/Component.h"

GameObject::GameObject() {
    isDead = false;
}

GameObject::~GameObject() {
    for (std::vector<Component*>::iterator it = components.end(); it != components.begin(); it--) {
        delete it-1;
    }
}

void GameObject::Update(float dt) {
    for (std::vector<Component *>::iterator it = components.end(); it != components.begin(); it--) {
        *(it-1).Update(dt);
    }
}

void GameObject::Render() {
    for (std::vector<Component *>::iterator it = components.end(); it != components.begin(); it--) {
        *(it - 1).Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
    component.push_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt) {
    bool cptFound = false;

    for (std::vector<Component *>::iterator it = components.end(); it != components.begin(); it--) {
        if (*it == cpt) {
            component.erase(it-1);
            cptFound = true;
        }
    }

    if (cpt == false) {
        std::cout << "No component found!" << std::endl;
    }
}

Component& GameObject::GetComponent(Component *cpt) {
    bool cptFound = false;

    for (std::vector<Component *>::iterator it = components.end(); it != components.begin(); it--) {
        if (*it == cpt) {
            cptFound = true;
            return *it;
        }
    }

    if (cpt == false) {
        std::cout << "No component found!" << std::endl;
        return nullptr;
    }
}
