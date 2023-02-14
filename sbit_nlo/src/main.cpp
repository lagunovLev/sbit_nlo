#include <iostream>
#include "game.h"
#include "scenes/initGame.h"
using namespace std;

int main()
{
    auto state = new InitGame();
    Game::run(state);
    return 0;
}