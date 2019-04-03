#include "../include/State.h"
#include "../include/GameObject.h"
#include "../include/Face.h"
#include "../include/Vec2.h"

#define BACKGROUND_SPRITE_PATH "assets/img/ocean.jpg"
#define BACKGROUND_MUSIC_PATH "assets/audio/stageState.ogg"
#define BACKGROUND_MUSIC_LOOP_TIMES -1 // -1 for infinite loop

#define ENEMY_SPRITE_PATH "assets/img/penguinface.png"
#define ENEMY_SOUND_PATH "assets/audio/boom.wav"

#define PI 3.141592

State::State() : bg(Sprite(BACKGROUND_SPRITE_PATH)),
                 music(BACKGROUND_MUSIC_PATH)
{
    quitRequested = false;
    music.Play(BACKGROUND_MUSIC_LOOP_TIMES);
}

void State::LoadAssets()
{
}

void State::Update(float dt)
{
    Input();
    for (int i = 0; i != int(objectArray.size()); i++)
    {
        objectArray[i]->Update(dt);
    }
    for (int i = 0; i != int(objectArray.size()); i++)
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
    for (int i = 0; i != int(objectArray.size()); i++)
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
                        // Aplica dano
                        face->Damage(std::rand() % 10 + 10);
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
                // Vec2 objPos = Vec2(200, 0).GetRotated(-PI + PI * (rand() % 1001) / 500.0) + Vec2(mouseX, mouseY);
                Vec2 objPos = Vec2(200, 0) + Vec2(mouseX, mouseY);
                AddObject((int)objPos.x, (int)objPos.y);
            }
        }
    }
}

void State::AddObject(int mouseX, int mouseY)
{
    GameObject enemy;
    enemy.box.x = mouseX;
    enemy.box.x = mouseY;
    // Criando o sprite do inimigo | Compensar tamanho do Sprite para a imagem ficar centralizada
    Sprite *enemy_sprite = new Sprite(enemy, ENEMY_SPRITE_PATH);
    enemy.AddComponent(enemy_sprite); 
    // Criando o som do inimigo
    Sound *enemy_sound = new Sound(enemy, ENEMY_SOUND_PATH);
    enemy.AddComponent(enemy_sound);
    // Criando a interface do inimigo
    Face *enemy_interface = new Face(enemy);
    enemy.AddComponent(enemy_interface);
    objectArray.emplace_back(enemy);
}
