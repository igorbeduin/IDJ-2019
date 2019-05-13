#include "../include/State.h"
#include "../include/GameObject.h"
#include "../include/Face.h"
#include "../include/Vec2.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"

State::State() : music(BACKGROUND_MUSIC_PATH),
                 quitRequested(false),
                 started(false)
{   
    music.Play(BACKGROUND_MUSIC_LOOP_TIMES);
    LoadAssets();

    // GameObject BACKGROUND
    // ====================================================
    GameObject *background = new GameObject();
    // Criando o sprite do background
    Sprite *bg_sprite = new Sprite(*background, BACKGROUND_SPRITE_PATH);
    background->AddComponent((std::shared_ptr<Sprite>)bg_sprite);
    // Criando o camera follower do background
    CameraFollower *bg_cmrFollower = new CameraFollower(*background);
    background->AddComponent((std::shared_ptr<CameraFollower>)bg_cmrFollower);

    background->box.x = 0;
    background->box.y = 0;

    // Adicionando o background no objectArray
    objectArray.emplace_back(background);

    // GameObject MAP
    // ====================================================
    GameObject *map = new GameObject();
    // Criando o tileSet para o tileMap
    TileSet *tileSet = new TileSet(*map, TILE_HEIGHT, TILE_WIDTH, MAP_TILESET_PATH);
    // Criando o tileMap
    TileMap *tileMap = new TileMap(*map, MAP_TILEMAP_PATH, tileSet);
    map->AddComponent((std::shared_ptr<TileMap>)tileMap);

    map->box.x = 0;
    map->box.y = 0;

    // Adicionando o mapa no objectArray
    objectArray.emplace_back(map);

    // GameObject ALIEN
    // ====================================================
    GameObject *alien = new GameObject();
    // Adicionando o comportamento de Alien
    Alien *behaviour = new Alien(*alien, 4);
    alien->AddComponent((std::shared_ptr<Alien>)behaviour);

    alien->box.x = 512;
    alien->box.y = 300;

    objectArray.emplace_back(alien);
}

State::~State()
{
    objectArray.clear();
}

void State::LoadAssets()
{
}

void State::Update(float dt)
{   
    // É importante que o Update da camera ocorra ANTES da atualização dos objetos
    // para que o background tenha sua movimentação compensada adequadamente.
    Camera::Update(dt);

    // Lida com eventos de quit a partir da interface de InputManager
    if ((InputManager::GetInstance().KeyPress(ESCAPE_KEY)) || (InputManager::GetInstance().QuitRequested()))
    {
        quitRequested = true;
    }

    for (int i = (int)objectArray.size() - 1; i >= 0; --i)
    {
        objectArray[i]->Update(dt);
    }
    for (int i = (int)objectArray.size() - 1; i >= 0; --i)
    {
        if (objectArray[i]->IsDead())
        {
            objectArray.erase(objectArray.begin() + i);
        }
    }


    SDL_Delay(dt);
}

void State::Render()
{
    for (int i = 0; i != (int)objectArray.size(); i++)
    {
        objectArray[i]->Render();
    }
}

bool State::QuitRequested()
{
    return quitRequested;
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go)
{
    std::shared_ptr<GameObject> shared_go(go);
    objectArray.push_back(shared_go);
    if (started)
    {
        shared_go->Start();
    }
    std::weak_ptr<GameObject> weak_go(shared_go);
    return weak_go;
}

void State::Start()
{
    LoadAssets();
    for (int i = 0; i < (int)objectArray.size(); i++)
    {
        objectArray[i]->Start();
    }
    started = true;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *go)
{
    for (int i = 0; i < (int)objectArray.size(); i++)
    {
        if (go == objectArray[i].get())
        {
            std::weak_ptr<GameObject> weak_go(objectArray[i]);
            return weak_go;
        }
    }
    std::weak_ptr<GameObject> empty_weak;
    return empty_weak;
}