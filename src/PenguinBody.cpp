#include "../include/PenguinBody.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"
#include "../include/Game.h"

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject &associated) : Component::Component(associated),
                                                   speed(0, 0),
                                                   linearSpeed(0),
                                                   angle(0),
                                                   hp(PENGUIN_HP)
{
    player = this;
    // Criando a sprite
    Sprite* pengBody_sprite = new Sprite(associated, PENGUINBODY_SPRITE_PATH);
    associated.AddComponent((std::shared_ptr<Sprite>)pengBody_sprite);
    Camera::Follow(&associated);

    // Adicionando Collider
    Collider *penguinBody_collider = new Collider(associated);
    associated.AddComponent((std::shared_ptr<Collider>)penguinBody_collider);
}

PenguinBody::~PenguinBody()
{
    Camera::Unfollow();
    player = nullptr;
}

void PenguinBody::Update(float dt)
{   
    if (hp <= 0)
    {
        associated.RequestDelete();

        // Criando animação de morte
        GameObject* penguin_death = new GameObject();
        Sprite *explosion_anim = new Sprite(*penguin_death, PENGUIN_DEATH_ANIM_PATH, PENGUIN_DEATH_ANIM_COUNT, 
                                                       PENGUIN_DEATH_ANIM_TIME / PENGUIN_DEATH_ANIM_COUNT, 
                                                       PENGUIN_DEATH_ANIM_TIME);
        penguin_death->AddComponent((std::shared_ptr<Sprite>)explosion_anim);
        // Criando som da morte
        Sound *explosion_sound = new Sound(*penguin_death, PENGUIN_DEATH_SOUND_PATH);
        penguin_death->AddComponent((std::shared_ptr<Sound>)explosion_sound);
        penguin_death->box.DefineCenter(associated.box.GetCenter());
        Game::GetInstance().GetCurrentState().AddObject(penguin_death);

        explosion_sound->Play();
    }

    if (InputManager::GetInstance().IsKeyDown(W_KEY))
    {
        if (linearSpeed < SPEED_LIM)
        {
            linearSpeed += PENGUIN_ACCELERATION;
        }
    }
    if (InputManager::GetInstance().IsKeyDown(S_KEY))
    {
        if (linearSpeed > -SPEED_LIM)
        {
            linearSpeed -= PENGUIN_ACCELERATION;
        }
    }

    if (InputManager::GetInstance().IsKeyDown(A_KEY))
    {
        associated.angleDeg -= ANG_SPEED;
    }
    if (InputManager::GetInstance().IsKeyDown(D_KEY))
    {
        associated.angleDeg += ANG_SPEED;
    }

    angle = associated.angleDeg / (180 / PI);
    Vec2 desloc = Vec2(cos(angle) * linearSpeed, sin(angle) * linearSpeed);
    Vec2 newPos = associated.box.GetCenter() + desloc;

    if (newPos.x > MAP_WIDTH)
    {
        newPos.x = MAP_WIDTH;
    }
    if (newPos.x < 0)
    {
        newPos.x = 0;
    }

    if (newPos.y > MAP_HEIGHT)
    {
        newPos.y = MAP_HEIGHT;
    }
    if (newPos.y < 0)
    {
        newPos.y = 0;
    }

    associated.box.DefineCenter(newPos);
}

void PenguinBody::Render()
{}

bool PenguinBody::Is(std::string type)
{
    return (type == "PenguinBody");
}

void PenguinBody::Start()
{}

void PenguinBody::NotifyCollision(GameObject &other)
{
    std::shared_ptr<Component> shared_Bullet = other.GetComponent("Bullet");

    // Se a colisão ocorre com uma bala
    if (shared_Bullet.get() != nullptr)
    {
        Bullet* bullet = (Bullet*)shared_Bullet.get();
        // Se quem atirou não foi o jogador, ou seja, ele mesmo
        if (!bullet->IsShooter("Player"))
        {
            int damage = bullet->GetDamage();
            hp -= damage;
            std::cout << "PENGUIN HP: " << hp << std::endl;
        }
    }
}

Vec2 PenguinBody::Pos()
{   
    return associated.box.GetCenter();
}
