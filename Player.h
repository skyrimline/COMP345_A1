#pragma once
#include <string>
#include <vector>
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
using namespace std;

class Player
{
public:
    Player(); // default constructor
    Player(string);
    Player(const Player &);
    Player(const Player &, string);                        // copy constructor
    Player &operator=(const Player &);                     // assignment operator
    friend ostream &operator<<(ostream &, const Player &); // stream insertion operator
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();
    void issueOrder(string);
    string getName() const;
    string toString() const;
    vector<Territory *> getTerritories();
    void addTerritory(Territory *territory);
    void addCards(Hand *);
    int *getArmies();
    void addArmies(int armies);
    bool isOwner(Continent *continent);
    bool isOwner(Territory *territory);

private:
    string name;
    vector<Territory *> terrs;
    vector<Card *> cards;
    vector<Order *> orders;
    int *armies;
};