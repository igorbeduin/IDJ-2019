#include "../include/Game.h"
#include "../include/StageState.h"

int main(int argc, char** argv) {
    Game& game = Game::GetInstance();

    StageState* initialState = new StageState();
    
    game.Push((State*)initialState);
    game.Run();

    return 0;
}