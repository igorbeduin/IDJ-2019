#pragma once

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE

#include "SDL_include.h"
#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"

class Sprite : public Component
{
public:
  Sprite(std::string file);
  Sprite(GameObject &associated);
  Sprite(GameObject &associated, std::string file, int frameCount = 1, float frameTime = 1);
  ~Sprite();
  void Open(std::string file);
  void SetClip(int x, int y,
               int w, int h);
  void Render();
  void Render(int x, int y);
  int GetWidth();
  int GetHeight();
  int GetWidthNoScale();
  int GetHeightNoScale();
  bool IsOpen();
  void Update(float dt);
  bool Is(std::string type);
  void SetScale(float scaleX, float scaleY);
  Vec2 GetScale();
  void SetFrame(int frame);
  void SetFrameCount(int frameCount);
  void SetFrameTime(float frameTime);

private:
  SDL_Texture *texture;
  int width;
  int height;
  SDL_Rect clipRect;
  Vec2 scale;
  int frameCount;
  int currentFrame;
  float timeElapsed;
  float frameTime;
};