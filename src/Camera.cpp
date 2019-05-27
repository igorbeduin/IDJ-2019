#include "../include/Camera.h"
#include "../include/InputManager.h"

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
            speed.x = (-1) * CAM_SPEED_FACTOR;
        }
        else
        {
            if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY))
            {
                speed.x = CAM_SPEED_FACTOR;
            }
            else
            {
                speed.x = 0;
            }
             
        }
        
        if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY))
        {
            speed.y = CAM_SPEED_FACTOR;
        }
        else
        {
            if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY))
            {
                speed.y = (-1) * CAM_SPEED_FACTOR;
            }
            else
            {
                speed.y = 0;
            }
        }
        pos.x += dt * speed.x;
        pos.y += dt * speed.y;
    }
    else
    {
        pos.x = -(focus->box.GetCenter().x) + (WINDOW_WIDTH / 2);
        pos.y = -(focus->box.GetCenter().y) + (WINDOW_HEIGHT / 2);
    }
    
}