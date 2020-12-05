#pragma once
#include <string>
#include <vector>
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include "GameObservers.h"
#include "PlayerStrategy.h"
using namespace std;

class Order;
class PlayerStrategy;

class Player
{
public:
    Player(); // default constructor
    Player(string);
    Player(const Player &);
    Player(const Player &, string);                        // copy constructor
    Player &operator=(const Player &);                     // assignment operator
    friend ostream &operator<<(ostream &, const Player &); // stream insertion operator
    string getName() const;
    string toString() const;
    vector<Territory *> getTerritories();
    void addTerritory(Territory *territory);
    void addCards(Hand *hand);
    int* getArmies();
    void addArmies(int armies);
    bool isOwner(Continent *continent);
    bool isOwner(Territory *territory);
    friend class Deploy;
    friend class Advance;
    friend class Airlift;
    friend class Bomb;
    friend class Blockade;
    friend class Negotiate;
    vector<Order*> getOrders();
    Hand* getHand();
    void setHand(Hand* hand);
    void clearOrders();
    void addOrder(Order* order);
    ~Player();
//    vector<Territory *> toAttack(Territory* source);
//    vector<Territory *> toDefend();
//    void issueOrder(string, Territory*, int);
//    void issueOrder(string, Territory*, Territory*, int);
//    void issueOrder(string, Territory*);
//    void issueOrder(string, Player*);
    //Player strategy methods
    void setStrategy(PlayerStrategy* s);
    void toAttack();
    //use the int i to let the game engine knows whether players should deploy in-hand armies or advance armies to defend
    //if i=1, deploy; i=2, advance
    void toDefend(int i);
    void issueOrder();

private:
    string* name;
    vector<Territory *> terrs;
    Hand* hand;
    vector<Order *> orders;//change to OrderList later
    int* armies;
    PlayerStrategy* strategy;
};
