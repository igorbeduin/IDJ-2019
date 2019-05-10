#include "../include/Vec2.h"
#include <math.h>

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

float Vec2::Distance(Vec2 begin, Vec2 end)
{   
    int x_distance = end.x - begin.x;
    int y_distance = end.y - begin.y;

    float distance = (float)sqrt(pow(x_distance, 2) + pow(y_distance, 2));

    return distance;
}

Vec2 Vec2::GetRotated(float theta)
{   
    int x_, y_;
    x_ = (x * cos(theta)) - (y * sin(theta));
    y_ = (y * cos(theta)) + (x * sin(theta));
    return Vec2(x_, y_);
}