#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "GameEngine.h"
using namespace std;

int main()
{
    srand(time(NULL));
    GameEngine game=GameEngine();
    game.startupPhase();
    game.mainGameLoop();
    return 0;
}