#pragma once

#include <memory>
#include <iostream>

#include "Vec2.h"

class Rect {
    public:
      Rect(float x, float y, float w, float h);
      Rect();
      bool Contains(float x, float y);
      float x, y, w, h;
      void DefineCenter(float x, float y);
      void DefineCenter(Vec2 box);
      Vec2 GetCenter();

};
