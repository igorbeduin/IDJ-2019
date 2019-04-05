#include "../include/Vec2.h"

Vec2::Vec2(int x, int y) : x(x),
                           y(y)
{
}
Vec2 Vec2::operator+(const Vec2 &other) const
{
    return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::GetRotated(float theta)
{
    // Logica de rotação
    return Vec2(x, y);
}