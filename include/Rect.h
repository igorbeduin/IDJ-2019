#pragma once

// #ifndef RECT_H
// #define RECT_H
#include <memory>
#include <iostream>

class Rect {
    public:
      Rect(float x, float y, float w, float h);
      bool Contains(float x, float y);
      float x = 0, y = 0, w = 0, h = 0;
};
