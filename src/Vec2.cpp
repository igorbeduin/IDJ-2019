#include "../include/Vec2.h"

Vec2::Vec2(int x, int y) : x(x)
                           y(y)
{
}

Vec2 Vec2::operator+(Vec2 &b)
{
    return Vec2(x + b.x, y + b.y);
}

Vec2 Vec2::GetRotated(float theta)
{
    return Vec2(x, y);
}