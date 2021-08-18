#include "Game/Game.hpp"

int main()
{
    GameManager game{ {800, 600} };
    return game.gameLoop();
}