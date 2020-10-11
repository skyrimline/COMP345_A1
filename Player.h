#ifndef PLAYER_H
#define PLAYER_H

#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include <iostream>
#include <vector>
using namespace std;

class Player {
public:
    Player();       // default constructor
    Player(string);
    Player(Player&, string);        // copy constructor
    Player& Player::operator=(Player&);      // assignment operator
    friend ostream& operator<<();           // stream insertion operator
    vector<Territory*> toAttack();
    vector<Territory*> toDefend();
    void issueOrder();
private:
    string name;
    vector<Territory*> terrs;
    vector<Card*> cards;
    vector<Order*> orders;
};

#endif