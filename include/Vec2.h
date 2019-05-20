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
  float ArgDeg();
  Vec2 GetRotated(float theta);
  Vec2 GetRotatedDeg(float theta);
  void RotateItself(float theta);
  Vec2 Rotate(float theta);
  void RotateDeg(float theta);
  float x, y;
  Vec2 operator+(const Vec2 &other) const;
  Vec2 operator-(const Vec2 &other) const;
  Vec2 operator*(const float &n) const;
};