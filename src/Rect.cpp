#include "../include/Rect.h"

Rect::Rect(float x, float y, float w, float h) : x(x),
                                                 y(y),
                                                 w(w),
                                                 h(h)
{
}

bool Rect::Contains(float x, float y)
{
    if ((x >= this->x)&&(x <= this->x + w)) 
    {
        if ((y >= this->y) && (y <= this->y + h))
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