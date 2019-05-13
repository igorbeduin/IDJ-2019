#include "../include/Rect.h"

Rect::Rect(float x, float y, float w, float h) : x(x),
                                                 y(y),
                                                 w(w),
                                                 h(h)
{
}

Rect::Rect() : Rect(0, 0, 0, 0)
{
}

bool Rect::Contains(float x, float y)
{
    if ((x >= this->x)&&(x <= this->x + this->w)) 
    {   
        if ((y >= this->y) && (y <= this->y + this->h))
        {
            return true;
        }
        else
        {
            return false;
        }
        
    }
    else 
    {
        return false;
    }
}

void Rect::DefineCenter(float x, float y)
{
    this->x = x - (this->w / 2);
    this->y = y - (this->h / 2);
}

void Rect::DefineCenter(Vec2 box)
{
    this->x = box.x - (this->w / 2);
    this->y = box.y - (this->h / 2);
}

Vec2 Rect::GetCenter()
{   
    Vec2 center = Vec2(this->x + (this->w / 2), this->y + (this->h / 2));
    return center;
}