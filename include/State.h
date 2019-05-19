#pragma once

#define BACKGROUND_SPRITE_PATH "assets/img/ocean.jpg"
#define BACKGROUND_MUSIC_PATH "assets/audio/stageState.ogg"
#define BACKGROUND_MUSIC_LOOP_TIMES -1 // -1 for infinite loop

#define ENEMY_SPRITE_PATH "assets/img/penguinface.png"
#define ENEMY_SOUND_PATH "assets/audio/boom.wav"
#define PI 3.141592

#define TILE_WIDTH 64
#define TILE_HEIGHT 64
#define MAP_TILEMAP_PATH "assets/map/tileMap.txt"
#define MAP_TILESET_PATH "assets/img/tileset.png"

#include <vector>
#include <memory>

#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "GameObject.h"
#include "TileMap.h"
#include "TileSet.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Collider.h"
#include "Collision.h"

class State
{
public:
  void Start();
  State();
  ~State();
  bool QuitRequested();
  void LoadAssets();
  void Update(float dt);
  void Render();
  std::weak_ptr<GameObject> AddObject(GameObject* go);
  std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);

private:
  Music music;
  bool quitRequested;
  void Input();
  std::vector<std::shared_ptr<GameObject>> objectArray;
  bool started;
};