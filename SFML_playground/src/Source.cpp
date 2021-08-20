#include "Game/Game.hpp"

int main()
{
    GameManager game{ {1200, 800} };
    return game.gameLoop();
}