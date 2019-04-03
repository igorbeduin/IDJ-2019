#pragma once

// #ifndef RECT_H
// #define RECT_H
#include <memory>

class Rect {
    public:
      bool Contains(float x, float y);
      float x, y, w, h;
};
