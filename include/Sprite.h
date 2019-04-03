#pragma once

// #ifndef SPRITE_H
// #define SPRITE_H

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE

#include "SDL_include.h"
#include "Component.h"
#include <memory>

class Sprite : public Component
{
public:
  Sprite(std::string file);
  Sprite(GameObject &associated);
  Sprite(GameObject &associated, std::string file);
  ~Sprite();
  void Open(std::string file);
  void SetClip(int x, int y,
               int w, int h);
  void Render();
  int GetWidth();
  int GetHeight();
  bool IsOpen();
  void Update(float dt);
  bool Is(std::string type);

private:
  SDL_Texture *texture;
  int width;
  int height;
  SDL_Rect clipRect;
};