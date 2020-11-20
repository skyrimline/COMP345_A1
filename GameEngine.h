#pragma once
#include <vector>
#include <iostream>
#include <random>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Map.h"
#include "MapLoader.h"
#include "Player.h"
#include "Cards.h"
#include "Orders.h"
#include "GameObservers.h"
using namespace std;

class GameEngine /*: public Subject*/
{
public:
    GameEngine();
    ~GameEngine();
    void startupPhase();
    void mainGameLoop();
    void reinforcementPhase();
    void issueOrderPhase(int);
    void executeOrderPhase();
    string getState();

private:
    string state;
    Map *gameMap;
    vector<Player *> players;
    Deck* deck;
};