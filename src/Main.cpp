#include "../include/Game.h"
#include "../include/StageState.h"

int main(int argc, char** argv) {
    Game& game = Game::GetInstance();

    StageState* initialState;
    
    game.Push(initialState);
    game.Run();

    return 0;
}