#include "../include/Vec2.h"

Vec2::Vec2(int x, int y) : x(x),
                           y(y)
{
}
Vec2::Vec2() : Vec2(0, 0)
{
}
Vec2 Vec2::operator+(const Vec2 &other) const
{
    return Vec2(x + other.x, y + other.y);
}


Vec2 Vec2::Distance(Vec2 begin, Vec2 end)
{
    int x_distance = end.x - begin.x;
    int y_distance = end.y - begin.y;

    return Vec2(x_distance, y_distance);
}

Vec2 Vec2::GetRotated(float theta)
{   
    int x_, y_;
    x_ = (x * cos(theta)) - (y * sin(theta));
    y_ = (y * cos(theta)) + (x * sin(theta));
    return Vec2(x_, y_);
}