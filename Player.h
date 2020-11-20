#pragma once
#include <string>
#include <vector>
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include "GameObservers.h"
using namespace std;

class Order;

class Subject{
public:
    virtual void Attach(Observer* o);
    virtual void Detach(Observer* o);
    virtual void Notify();
    Subject();
    ~Subject();
private:
    list<Observer*> *_observers;
};

class Player:public Subject
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
    string getName() const;
    string toString() const;
    vector<Territory *> getTerritories();
    void addTerritory(Territory *territory);
    void addCards(Hand *hand);
    int *getArmies();
    void addArmies(int armies);
    bool isOwner(Continent *continent);
    bool isOwner(Territory *territory);
    friend class Deploy;
    friend class Advance;
    friend class Airlift;
    friend class Bomb;
    friend class Blockade;
    friend class Negotiate;
    void issueOrder(string, Territory*, int);
    void issueOrder(string, Territory*, Territory*, int);
    void issueOrder(string, Territory*);
    void issueOrder(string, Player*);
    vector<Order*> getOrders();
    Hand* getHand();
    void setHand(Hand* hand);

private:
    string name;
    vector<Territory *> terrs;
    Hand* hand;
    vector<Order *> orders;
    int *armies;
    string* phase;
};
