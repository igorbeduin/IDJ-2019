#pragma once

// #ifndef VEC2_H
// #define VEC2_H

#include <memory>

class Vec2
{
public:
  Vec2(int x, int y);
  Vec2 GetRotated(float theta);
  float x, y;
  Vec2 operator+(const Vec2 &other) const;
};