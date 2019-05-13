#include "../include/Alien.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"
#include "../include/Vec2.h"
#include "../include/Game.h"

Alien::Action::Action(ActionType type, float x, float y) : type(type),
                                                           pos(x, y)
{
}

// speed já está sendo inicializado pelo construtor de Vec2
Alien::Alien(GameObject &associated, int nMinions) : Component::Component(associated),
                                                     hp(50),
                                                     nMinions(nMinions)
{
    // Adicionando o sprite do alien
    Sprite *alien_sprite = new Sprite(associated, ALIEN_SPRITE_PATH);
    associated.AddComponent((std::shared_ptr<Sprite>)alien_sprite);
}

void Alien::Start()
{
    std::weak_ptr<GameObject> weak_alien = Game::GetInstance().GetState().GetObjectPtr(&associated);

    // Criando minions
    for (int i = 0; i < nMinions; i++)
    {
        GameObject *minion = new GameObject();
        Minion *minion_behaviour = new Minion(*minion, weak_alien, i * PI / 2);
        minion->AddComponent((std::shared_ptr<Minion>)minion_behaviour);

        std::weak_ptr<GameObject> weak_minion = Game::GetInstance().GetState().AddObject(minion);
        minionArray.push_back(weak_minion);
    }
}

Alien::~Alien()
{

    for (int i = minionArray.size() - 1; i >= 0; i--)
    {
        minionArray.erase(minionArray.begin() + i);
    }
}

void Alien::Update(float dt)
{
    // Enfileiramento de novas ações
    if (InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT))
    {
        taskQueue.emplace(Action(SHOOT, InputManager::GetInstance().GetMouseX(),
                                        InputManager::GetInstance().GetMouseY()));
    }
    if (InputManager::GetInstance().MousePress(SDL_BUTTON_RIGHT))
    {
        taskQueue.emplace(Action(MOVE, InputManager::GetInstance().GetMouseX(),
                                       InputManager::GetInstance().GetMouseY()));
    }

    // Execução da fila de ações
    if (!taskQueue.empty())
    {
        switch (taskQueue.front().type)
        {
            case MOVE:
            {
                float step = dt * ALIEN_VELOCITY;

                // Calculo de velocidade e mudança de posição
                Vec2 distance = Vec2::Distance(Vec2(associated.box.x + associated.box.w / 2, associated.box.y + associated.box.h / 2), taskQueue.front().pos);

                if (distance.Magnitude() > step)
                {
                    associated.box.x += step * cos(distance.Arg());
                    associated.box.y += step * sin(distance.Arg());
                }
                else
                {
                    associated.box.x = action.pos.x - associated.box.w / 2;
                    associated.box.y = action.pos.y - associated.box.h / 2;
                    taskQueue.pop();
                }
                break;
            }

            case SHOOT:
            {
                // TODO: ESCOLHER O MINION ALEATORIAMENTE E FAZER O SHOOT DE FATO
                taskQueue.pop();
                break;
            }
        }
    }
}

void Alien::Render()
{
}

bool Alien::Is(std::string type)
{
    return (type == "Alien");
}
