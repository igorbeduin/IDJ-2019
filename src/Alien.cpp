#include "../include/Alien.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"
#include "../include/Vec2.h"

Alien::Action::Action(ActionType type, float x, float y) : type(type),
                                                           pos(x, y)
{

}

// speed já está sendo inicializado pelo construtor de Vec2
Alien::Alien(GameObject& associated, int nMinions) : Component::Component(associated),
                                                     hp(0)
{
    // Adicionando o sprite do alien
    Sprite *alien_sprite = new Sprite(associated, ALIEN_SPRITE_PATH);
    associated.AddComponent((std::shared_ptr<Sprite>)alien_sprite);
}

void Alien::Start()
{
    /*
        TODO:
        - voltar aqui depois que o alien tiver funcionando
    */
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
        taskQueue.emplace(Action(SHOOT, InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                                        InputManager::GetInstance().GetMouseY() + Camera::pos.y));
    }
    if (InputManager::GetInstance().MousePress(SDL_BUTTON_RIGHT))
    {
        std::cout << "ADICIONEI A ACTION CORRETA" << std::endl;
        taskQueue.emplace(Action(MOVE, InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                                       InputManager::GetInstance().GetMouseY() + Camera::pos.y));
    }

    // Execução da fila de ações
    if (!taskQueue.empty())
    {
        if (taskQueue.front().type == MOVE)
        {
            std::cout << "EXECUTANDO A ACTION CORRETA" << std::endl;
            int x_signal = 1;
            int y_signal = 1;
            if (taskQueue.front().pos.x < associated.box.x)
            {
                x_signal = -1;
            }
            if (taskQueue.front().pos.y < associated.box.y)
            {
                y_signal = -1;
            }

            // Calculo de velocidade e mudança de posição
            float distance = Vec2::Distance(Vec2(associated.box.x, associated.box.y), taskQueue.front().pos);
            std::cout << "distance: " << distance << std::endl;
            
            // associated.box.x += dt * ALIEN_VELOCITY * (x_signal);
            associated.box.y += dt * ALIEN_VELOCITY * (y_signal);
            // associated.box.DefineCenter(associated.box.x + (2 * (x_signal)), associated.box.y + (2 * (y_signal)));

            if (distance < MIN_DIST)
            {
                associated.box.DefineCenter(taskQueue.front().pos.x, taskQueue.front().pos.y);
                taskQueue.pop();
            }
            //taskQueue.pop();
        }
        if (taskQueue.front().type == SHOOT)
        {
            // Execução de tiro
            taskQueue.pop();
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

