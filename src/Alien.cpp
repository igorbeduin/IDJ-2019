#include "../include/Alien.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"
#include "../include/Vec2.h"
#include "../include/Game.h"
#include "../include/PenguinBody.h"

int Alien::alienCount = 0;

// speed já está sendo inicializado pelo construtor de Vec2
Alien::Alien(GameObject &associated, int nMinions) : Component::Component(associated),
                                                     state(RESTING),
                                                     hp(ALIEN_HP),
                                                     nMinions(nMinions)
{
    alienCount += 1;
    // Adicionando o sprite do alien
    Sprite *alien_sprite = new Sprite(associated, ALIEN_SPRITE_PATH);
    associated.AddComponent((std::shared_ptr<Sprite>)alien_sprite);

    // Adicionando Collider
    Collider* alien_collider = new Collider(associated);
    associated.AddComponent((std::shared_ptr<Collider>)alien_collider);
}

void Alien::Start()
{
    std::weak_ptr<GameObject> weak_alien = Game::GetInstance().GetCurrentState().GetObjectPtr(&associated);

    // Criando minions
    for (int i = 0; i < nMinions; i++)
    {
        GameObject *minion = new GameObject();
        Minion *minion_behaviour = new Minion(*minion, weak_alien, i * 360/nMinions);
        minion->AddComponent((std::shared_ptr<Minion>)minion_behaviour);

        std::weak_ptr<GameObject> weak_minion = Game::GetInstance().GetCurrentState().AddObject(minion);
        minionArray.push_back(weak_minion);
    }
}

Alien::~Alien()
{
    alienCount -= 1;
    for (int i = minionArray.size() - 1; i >= 0; i--)
    {
        minionArray.erase(minionArray.begin() + i);
    }
}

void Alien::Update(float dt)
{   
    // Verifica morte
    if (hp <= 0)
    {
        associated.RequestDelete();

        // Criando animação de morte
        GameObject *alien_death = new GameObject();
        Sprite *explosion_anim = new Sprite(*alien_death, ALIEN_DEATH_ANIM_PATH, ALIEN_DEATH_ANIM_COUNT,
                                                     ALIEN_DEATH_ANIM_TIME / ALIEN_DEATH_ANIM_COUNT,
                                                     ALIEN_DEATH_ANIM_TIME);
        alien_death->AddComponent((std::shared_ptr<Sprite>)explosion_anim);
        // Criando som da morte
        Sound *explosion_sound = new Sound(*alien_death, ALIEN_DEATH_SOUND_PATH);
        alien_death->AddComponent((std::shared_ptr<Sound>)explosion_sound);
        alien_death->box.DefineCenter(associated.box.GetCenter());
        Game::GetInstance().GetCurrentState().AddObject(alien_death);

        explosion_sound->Play();
    }

    // Faz o alien girar
    associated.angleDeg += dt * ALIEN_ANG_VEL;

    // FSM de ações do Alien
    switch (state) 
    {   
        // Pega posição do player
        if (PenguinBody::player != nullptr)
        {
            destination = PenguinBody::player->Pos();
        }

        // Se ele estiver se movendo
        case MOVING:
        {
            // Se a distancia for maior que uma tolerancia, SE MOVE até o destino
            if (Vec2::Distance(associated.box.GetCenter(), destination).Magnitude() > ALIEN_TARGET_TOLERANCE)
            {
                float step = dt * ALIEN_VELOCITY;

                // Calculo de velocidade e mudança de posição
                Vec2 distance = Vec2::Distance(associated.box.GetCenter(), destination);
                // Anda até o destino
                if (distance.Magnitude() > step)
                {
                    associated.box.x += step * cos(distance.Arg());
                    associated.box.y += step * sin(distance.Arg());
                }
                // Teleporta pro destino (lida com "vibrações")
                else
                {
                    associated.box.DefineCenter(destination);
                }
            }
            // Se a distancia for menor que uma tolerancia, ATIRA
            else
            {
                std::shared_ptr<GameObject> minion;
                Vec2 target = destination;

                float distToTarget = std::numeric_limits<float>::max();

                // Percorre o vector de minions procurando pelo mais próximo do target
                // No final do laço, temos em "minion" o shared_ptr para o minion mais próximo do target
                if (!minionArray.empty())
                {
                    for (int i = 0; i < (int)minionArray.size(); i++)
                    {
                        if (!minionArray[i].expired())
                        {
                            std::shared_ptr<GameObject> temp_minion = minionArray[i].lock();
                            float closerMinionDistance = Vec2::Distance(temp_minion->box.GetCenter(), target).Magnitude();

                            if (closerMinionDistance < distToTarget)
                            {
                                distToTarget = closerMinionDistance;
                                minion = temp_minion;
                            }
                        }
                    }
                }

                // Se esse minion existir
                if (minion.get() != nullptr)
                {
                    Minion* real_minion = (Minion *)minion->GetComponent("Minion").get();
                    // Atira
                    if (PenguinBody::player != nullptr)
                    {
                        std::cout << "ALIEN: HAAAA! PEW" << std::endl;
                        real_minion->Shoot(target);
                    }
                }
                else
                {
                    std::cout << "ERRO: não existe minion pra atirar" << std::endl;
                }

                // Reseta o timer e muda o estado para RESTING
                restTimer.Restart();
                state = RESTING;
            }
        }
        case RESTING:
        {   
            // Se o timer já tiver "estourado"
            if (restTimer.Get() >= ALIEN_MOV_COOLDOWN)
            {   
                // Atualiza a posição do destino/target e muda o estado para MOVING
                if (PenguinBody::player != nullptr)
                {
                    destination = PenguinBody::player->Pos();
                }
                state = MOVING;

            }
            else
            {
                // Tempoa aleatório adicionado no update 
                // para avançar o tempo e evitar que os aliens ajam sincronizadamente.
                float randomTime = (rand() % 500 / 1000); 
                // Atualiza o timer até ele "estourar".
                restTimer.Update(dt + randomTime);
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

void Alien::NotifyCollision(GameObject &other)
{
    std::shared_ptr<Component> shared_Bullet = other.GetComponent("Bullet");

    // Se a colisão ocorre com uma bala
    if (shared_Bullet.get() != nullptr)
    {
        Bullet *bullet = (Bullet *)shared_Bullet.get();
        // Se quem atirou não foi o inimigo, ou seja, ele mesmo
        if (!bullet->IsShooter("Enemy"))
        {
            int damage = bullet->GetDamage();
            hp -= damage;
            std::cout << "ALIEN HP: " << hp << std::endl;
        }
    }
}
