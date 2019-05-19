#include "../include/PenguinBody.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"

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
    player = nullptr;
    Camera::Unfollow();
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
        Game::GetInstance().GetState().AddObject(penguin_death);
        
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

    angle = associated.angleDeg / (180 / 3.14159265359);
    Vec2 desloc = Vec2(cos(angle) * linearSpeed, sin(angle) * linearSpeed);
    associated.box.DefineCenter(associated.box.GetCenter() + desloc);
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

    if (shared_Bullet.get() != nullptr)
    {
        Bullet* bullet = (Bullet*)shared_Bullet.get();
        if (!bullet->FromPlayer())
        {
            int damage = bullet->GetDamage();
            std::cout << "PUNGUIM SOFREU " << damage << std::endl;
            hp -= damage;
        }
    }
}
