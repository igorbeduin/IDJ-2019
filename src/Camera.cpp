#include "../include/Camera.h"

void Camera::Follow(GameObject* newFocus)
{
    focus = newFocus;
}

void Unfollow()
{
    focus = nullptr;
}