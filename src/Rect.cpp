#include "../include/Rect.h"

bool Rect::Contains(float x, float y)
{
    if ((x >= this.x)&&(x <= this.x + w)) 
    {
        if ((y >= this.y) && (y <= this.y + h))
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