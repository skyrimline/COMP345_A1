#pragma once
#include <iostream>
#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "Orders.h"
using namespace std;

class PlayerStrategy {
public:
    virtual void issueOrder(Player* p, int i) = 0;
    virtual void toAttack(Player* p) = 0;
    virtual void toDefend(Player* p) = 0;
};

class HumanPlayerStrategy:public PlayerStrategy{
public:
    void issueOrder(Player* player, int i);
    void toAttack(Player* player);
    void toDefend(Player* player);
};

class AggressivePlayerStrategy:public PlayerStrategy{
public:
    void issueOrder(Player* player, int i);
    void toAttack(Player* player);
    void toDefend(Player* player);
};

class BenevolentPlayerStrategy:public PlayerStrategy{
public:
    void issueOrder(Player* player, int i);
    void toAttack(Player* player);
    void toDefend(Player* player);
};

class NeutralPlayerStrategy:public PlayerStrategy{
public:
    void issueOrder(Player* player, int i);
    void toAttack(Player* player);
    void toDefend(Player* player);
};