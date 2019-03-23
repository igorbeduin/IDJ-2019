#include <iostream>
#include "include/Game.hpp"
#include "include/Sprite.hpp"
#include "include/Music.hpp"
#include "include/State.hpp"


int main(int argc, char** argv) {
    Game& game = Game::GetInstance();
    game.Run();

    return 0;
}

// A janela deve ter as dimensões 1024x600, e o título deve ser seu nome e matrícula.