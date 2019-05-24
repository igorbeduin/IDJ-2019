#include "../include/EndState.h"
#include "../include/GameData.h"

EndState::EndState() : State::State()
{   
    // TODO: component de text que diz para o jogador 
    // apertar ESC para voltar para o menu ou SPACEBAR
    // para jogar novamente

    if (GameData::playerVictory)
    {
        // TODO: objeto de vitoria

    }
    else
    {
        // TODO: objeto de derrota
    }
}

void EndState::LoadAssets()
{}
void EndState::Update(float dt)
{
    // TODO: Verificar condições de vitoria e derrota
}
void EndState::Render()
{}

void EndState::Start()
{}
void EndState::Pause()
{}
void EndState::Resume()
{}