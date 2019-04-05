#include "../include/State.h"
#include "../include/GameObject.h"
#include "../include/Face.h"
#include "../include/Vec2.h"

#define BACKGROUND_SPRITE_PATH "assets/img/ocean.jpg"
#define BACKGROUND_SOUND_PATH "assets/audio/stageState.ogg"
#define BACKGROUND_SOUND_LOOP_TIMES -1 // -1 for infinite loop

#define ENEMY_SPRITE_PATH "assets/img/penguinface.png"
#define ENEMY_SOUND_PATH "assets/audio/boom.wav"

#define PI 3.141592

State::State() : bg_sprite(new Sprite(background, BACKGROUND_SPRITE_PATH)),
                 bg_sound(new Sound(background, BACKGROUND_SOUND_PATH))
{   
    background.AddComponent(bg_sprite);
    background.AddComponent(bg_sound);
    objectArray.emplace_back(&background);
    LoadAssets();
    quitRequested = false;
    Sound *sound = (Sound *)background.GetComponent("Sound");
    sound->Play();
}

State::~State()
{
    for (int i = objectArray.size() - 1; i >= 0; --i)
    {
        // Garantia de "delete" do unique_ptr
        objectArray[i].reset(nullptr);
        objectArray.erase(objectArray.begin() + i);
    }
}

void State::LoadAssets()
{
}

void State::Update(float dt)
{   
    Input();
    for (int i = (int)objectArray.size() - 1; i >=0 ; --i)
    {   
        GameObject *go = (GameObject *)objectArray[i].get();
        go->Update(dt);
    }
    for (int i = (int)objectArray.size() - 1; i >=0 ; --i)
    {
        if (objectArray[i]->IsDead())
        {   
            GameObject *go = (GameObject *)objectArray[i].get();
            Sound *sound = (Sound *)go->GetComponent("Sound");
            sound->Play();
            // Garantia de "delete" do unique_ptr
            objectArray[i].reset(nullptr);
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

void State::Input()
{
    SDL_Event event;
    int mouseX, mouseY;

    // Obtenha as coordenadas do mouse
    SDL_GetMouseState(&mouseX, &mouseY);

    // SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
    while (SDL_PollEvent(&event))
    {
        // Se o evento for quit, setar a flag para terminação
        if (event.type == SDL_QUIT)
        {
            quitRequested = true;
        }

        // Se o evento for clique...
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            // Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
            for (int i = int(objectArray.size()) - 1; i >= 0; --i)
            {
                // Obtem o ponteiro e casta pra Face.
                GameObject *go = (GameObject *)objectArray[i].get();
                // Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
                // O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
                // ao usar get(), violamos esse princípio e estamos menos seguros.
                // Esse código, assim como a classe Face, é provisório. Futuramente, para
                // chamar funções de GameObjects, use objectArray[i]->função() direto.

                if (go->box.Contains(float(mouseX), float(mouseY)))
                {   
                    Face *face = (Face *)go->GetComponent("Face");
                    if (nullptr != face)
                    {   
                        int damage = std::rand() % 10 + 10;
                        std::cout << "Damage applied: " << damage << std::endl;
                        // Aplica dano
                        face->Damage(damage);
                        // Sai do loop (só queremos acertar um)
                        break;
                    }
                }
            }
        }
        if (event.type == SDL_KEYDOWN)
        {
            // Se a tecla for ESC, setar a flag de quit
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                quitRequested = true;
            }
            // Se não, crie um objeto
            else
            {
                Vec2 objPos = Vec2(200, 0).GetRotated(-PI + PI * (rand() % 1001) / 500.0) + Vec2(mouseX, mouseY);
                AddObject((int)objPos.x, (int)objPos.y);
            }
        }
    }
}

void State::AddObject(int mouseX, int mouseY)
{   
    GameObject *enemy = new GameObject();
    // Criando o sprite do inimigo
    Sprite *enemy_sprite = new Sprite(*enemy, ENEMY_SPRITE_PATH);
    enemy->AddComponent(enemy_sprite);
    // Criando o som do inimigo
    Sound *enemy_sound = new Sound(*enemy, ENEMY_SOUND_PATH);
    enemy->AddComponent(enemy_sound);
    // Criando a interface do inimigo
    Face *enemy_interface = new Face(*enemy);
    enemy->AddComponent(enemy_interface);

    enemy->box.x = mouseX - (enemy_sprite->GetWidth())/2;
    enemy->box.y = mouseY - (enemy_sprite->GetHeight())/2;

    // Adicionando o inimigo no objectArray
    objectArray.emplace_back(enemy);
}
