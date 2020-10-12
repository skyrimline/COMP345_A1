#include "Player.h"
#include <iostream>
#include <vector>
using namespace std;

Player::Player() {
    this->name = "";
}

Player::Player(Player& p) {
    this->name = p.name;
}

Player::Player(string pName) {
    this->name = pName;
}

Player::Player(Player& p, string pName) {
    for (vector<Territory*>::iterator it = p.terrs.begin(); it != p.terrs.end(); ++it) {
        this->terrs.push_back(*it);
    }
    this->name = pName;
}

Player& Player::operator=(Player& p) {
    Player* p1 = new Player(p);
    Player& pCopy = *p1;
    return pCopy;
}

ostream& operator<<(ostream &out, const Player &p) {
    out << p.to_String();
    out << endl;
    return out; 
}

vector<Territory*> Player::toAttack() {
    // for now only arbitary territory list returned
    vector<Territory*> terrAttack;
    for (vector<Territory*>::iterator it = terrs.begin(); it != terrs.end(); ++it) {
        terrAttack.push_back(*it);
    }
    return terrAttack;
}

vector<Territory*> Player::toDefend() {
    // for now only arbitary territory list returned
    vector<Territory*> terrDefend;
    for (vector<Territory*>::iterator it = terrs.begin(); it != terrs.end(); ++it) {
        terrDefend.push_back(*it);
    }
    return terrDefend;
}

void Player::issueOrder(string ){
    Order* ord = new Order();
    orders.push_back(ord);
}

string Player::to_String() {
    string pInfo = "";
    pInfo += "Player " + *this.getName() + "\'s info: \n";
    pInfo += "\tTerritory owned: \n";
    for(vector<Territory>::iterator it = this->terrs.begin(); it != this->terrs.end(); ++i) {
        pInfo +=  it->to_String() + ", ";
    }
    pInfo += "\n\tCards owned: \n";
    for(vector<Card>::iterator it = this->cards.begin(); it != this->cards.end(); ++i) {
        pInfo += it->to_String() + ", ";
    }
    pInfo += "\n";
    return pInfo;
}

string Player::getName()
{
    return name;
}
