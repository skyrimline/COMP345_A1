#pragma once
#include <vector>
#include <iostream>
#include <random>
#include <fstream>
#include "Map.h"
#include "MapLoader.h"
#include "Player.h"
#include "Cards.h"
#include "Orders.h"
using namespace std;

class GameEngine
{
public:
    GameEngine();
    void startupPhase();
    void mainGameLoop();
    void reinforcementPhase();
    void issueOrderPhase();
    void exeuteOrderPhase();
private:
    Map *gameMap;
    vector<Player*> players;
    Hand *cards;
};