#include <iostream>
#include <Game.hpp>
#include <Sprite.hpp>
#include <Music.hpp>
#include <State.hpp>


int main(int argc, char** argv) {
    std::string title;
    // dimensoes da janela do jogo
    int width = 1024;
    int height = 600;
    Game game;

    title = "Igor R. O. Beduin - 14/0143882"
    game = new Game(title, width, height);
    game.Run();
    delete game;

    return 0;
}

// A janela deve ter as dimensões 1024x600, e o título deve ser seu nome e matrícula.