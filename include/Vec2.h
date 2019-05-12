#pragma once

#include <memory>
#include <iostream>
#include <math.h>

class Vec2
{
public:
  Vec2(float x, float y);
  Vec2();
  static Vec2 Distance(Vec2 begin, Vec2 end);
  float Magnitude();
  float Arg();
  Vec2 GetRotated(float theta);
  void Rotate(float theta);
  float x, y;
  Vec2 operator+(const Vec2 &other) const;
  Vec2 operator-(const Vec2 &other) const;
};