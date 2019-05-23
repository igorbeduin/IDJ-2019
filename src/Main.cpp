#include "../include/Game.h"
#include "../include/TitleState.h"

int main(int argc, char** argv) {
    Game& game = Game::GetInstance();

    TitleState* initialState = new TitleState();
    
    game.Push(initialState);
    game.Run();

    return 0;
}