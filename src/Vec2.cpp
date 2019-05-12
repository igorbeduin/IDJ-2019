#include "../include/Vec2.h"

Vec2::Vec2(float x, float y) : x(x),
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
    float x_distance = end.x - begin.x;
    float y_distance = end.y - begin.y;

    return Vec2(x_distance, y_distance);
}

void Vec2::Rotate(float theta)
{   

    float x_ = (x * cos(theta)) - (y * sin(theta));
    float y_ = (x * sin(theta)) + (y * cos(theta));

    x = x_;
    y = y_;
}

Vec2 Vec2::GetRotated(float theta)
{   
    Vec2 temp(x, y);
    temp.Rotate(theta);

    return temp;
}

float Vec2::Magnitude()
{
    return (float)sqrt(pow(x, 2) + pow(y, 2));
}

float Vec2::Arg()
{
    return atan2(y, x);
}