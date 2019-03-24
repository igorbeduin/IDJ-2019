#include "../include/Game.hpp"

int main(int argc, char** argv) {
    Game& game = Game::GetInstance();
    game.Run();
    // TODO: TRATAR ERROS DE INICIALIZACAO COM TRY/CATCH

    return 0;
}