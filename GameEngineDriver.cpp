#include <iostream>
#include <vector>
#include "GameEngine.h"
using namespace std;

int main()
{
    GameEngine game=GameEngine();
    game.startupPhase();
    game.mainGameLoop();
    return 0;
}