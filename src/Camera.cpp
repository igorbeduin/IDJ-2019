#include "../include/Camera.h"
#include "../include/InputManager.h"

#define SPEED 100

GameObject* Camera::focus;

Vec2 Camera::pos;
Vec2 Camera::speed;

void Camera::Follow(GameObject* newFocus)
{
    focus = newFocus;
}

void Camera::Unfollow()
{
    focus = nullptr;
}

void Camera::Update(float dt)
{
    if (focus == nullptr) 
    {
        if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY))
        {
            speed.x = (-1) * SPEED;
        }
        else
        {
            if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY))
            {
                speed.x = SPEED;
            }
            else
            {
                speed.x = 0;
            }
             
        }
        
        if (InputManager::GetInstance().IsKeyDown(UP_ARROW_EY))
        {
            speed.y = SPEED;
        }
        else
        {
            if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY))
            {
                speed.y = (-1) * SPEED;
            }
            else
            {
                speed.y = 0;
            }
        }
        pos.x += dt * speed.x;
        pos.y += dt * speed.y;
    }
}