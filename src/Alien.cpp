#include "../include/Alien.h"

Alien::Alien(GameObject& associated, int nMinions) : speed(0, 0),
                                                     hp(0)
{
    /*
        TODO:
        - Adicionar componente do tipo Sprite ao associated;
        ... (voltar aqui)
    */
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
    /*
        TODO:
    */
}

void Alien::Render()
{

}

bool Alien::Is(std::string type)
{
    return (type == "Alien");
}

