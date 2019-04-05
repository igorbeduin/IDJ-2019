#pragma once

// #ifndef RECT_H
// #define RECT_H
#include <memory>

class Rect {
    public:
      bool Contains(float x, float y);
      float x = 0, y = 0, w = 0, h = 0;
};
