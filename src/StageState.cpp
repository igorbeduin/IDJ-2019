#include "../include/StageState.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"

StageState::StageState() : State::State()
{   
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

    // Adicionando o background no objectArray
    AddObject(background);

    // GameObject MAP
    // ====================================================
    GameObject *map = new GameObject();
    // Criando o tileSet para o tileMap
    TileSet *tileSet = new TileSet(*map, TILE_HEIGHT, TILE_WIDTH, MAP_TILESET_PATH);
    // Criando o tileMap
    TileMap *tileMap = new TileMap(*map, MAP_TILEMAP_PATH, tileSet);
    map->AddComponent((std::shared_ptr<TileMap>)tileMap);

    AddObject(map);

    // GameObject PENGUIN
    // ====================================================
    GameObject *penguinBody = new GameObject(704, 640);
    // Adicionando o comportamento do PenguinBody
    PenguinBody* penguinBody_behaviour = new PenguinBody(*penguinBody);
    penguinBody->AddComponent((std::shared_ptr<PenguinBody>)penguinBody_behaviour);

    std::weak_ptr<GameObject> weak_penguin = AddObject(penguinBody);

    // GameObject CANNON PENGUIN
    // ====================================================
    GameObject *penguinCannon = new GameObject();
    // Adicionando o comportamento do PenguinCannon
    PenguinCannon* penguinCannon_behaviour = new PenguinCannon(*penguinCannon, weak_penguin);
    penguinCannon->AddComponent((std::shared_ptr<PenguinCannon>)penguinCannon_behaviour);

    AddObject(penguinCannon);

    // GameObject ALIEN
    // ====================================================
    GameObject *alien = new GameObject(512, 300);
    // Adicionando o comportamento de Alien
    Alien *alien_behaviour = new Alien(*alien, 4);
    alien->AddComponent((std::shared_ptr<Alien>)alien_behaviour);

    AddObject(alien);
}

void StageState::LoadAssets()
{
}

void StageState::Update(float dt)
{   
    // É importante que o Update da camera ocorra ANTES da atualização dos objetos
    // para que o background tenha sua movimentação compensada adequadamente.
    Camera::Update(dt);

    // Lida com eventos de quit a partir da interface de InputManager
    if ((InputManager::GetInstance().KeyPress(ESCAPE_KEY)) || (InputManager::GetInstance().QuitRequested()))
    {
        quitRequested = true;
    }

    // Update dos GOs
    for (int i = (int)objectArray.size() - 1; i >= 0; --i)
    {
        objectArray[i]->Update(dt);
    }

    // Verifica se há colisões
    std::vector<std::shared_ptr<GameObject>> objWithCollider;
    for (int i = (int)objectArray.size() - 1; i >= 0; i--)
    {   
        std::shared_ptr<Component> colliderComponent = objectArray[i]->GetComponent("Collider");
        if (colliderComponent.get() != nullptr)
        {
            objWithCollider.push_back(objectArray[i]);
            for (int j = 0; j < (int)objWithCollider.size(); j++)
            {
                if (objectArray[i] != objWithCollider[j])
                {
                    if (Collision::IsColliding(objectArray[i]->box, objWithCollider[j]->box, objectArray[i]->GetAngleRad(), objWithCollider[j]->GetAngleRad()))
                    {
                        objectArray[i]->NotifyCollision(*objWithCollider[j].get());
                        objWithCollider[j]->NotifyCollision(*objectArray[i].get());
                    }
                }
            }
        }
    }

    // Verifica se algum objeto deve ser deletado depois de ser atualizado
    for (int i = (int)objectArray.size() - 1; i >= 0; --i)
    {
        if (objectArray[i]->IsDead())
        {
            objectArray.erase(objectArray.begin() + i);
        }
    }

    
    SDL_Delay(dt);
}

void StageState::Render()
{
    for (int i = 0; i != (int)objectArray.size(); i++)
    {
        objectArray[i]->Render();
    }
}

void StageState::Start()
{
    LoadAssets();
    for (int i = 0; i < (int)objectArray.size(); i++)
    {
        objectArray[i]->Start();
    }
    started = true;
}

void StageState::Pause()
{}

void StageState::Resume()
{}