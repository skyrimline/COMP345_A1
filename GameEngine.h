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

class Subject {
public:
    virtual void Attach(Observer* o);
    virtual void Detach(Observer* o);
    virtual void Notify();
    Subject();
    ~Subject();
private:
    list<Observer*>* _observers;
};

class GameEngine: public Subject{
public:
    GameEngine();
    ~GameEngine();
    string getState();
    void startupPhase();
    void mainGameLoop();
    void reinforcementPhase();
    void issueOrderPhase(int i);
    void executeOrderPhase();

private:
    Map *gameMap;
    vector<Player *> players;
    Deck* deck;
    string state;
};