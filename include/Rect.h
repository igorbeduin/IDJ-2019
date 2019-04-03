#pragma once

// #ifndef RECT_H
// #define RECT_H

class Rect {
    public:
      bool Contains(float x, float y);
      float x, y, w, h;
};
