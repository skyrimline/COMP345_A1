#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
using namespace std;

class Map;
class Card;
class Order;
class Territory;

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
    vector<Territory*> getTerritories();
    void addTerritory(Territory* territory);

private:
    string name;
    vector<Territory *> terrs;
    vector<Card *> cards;
    vector<Order *> orders;
};
#endif //PLAYER_H