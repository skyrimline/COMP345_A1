#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include "Cards.h"
#include <vector>
using namespace std;

Player::Player()
{
    this->name = "";
}

Player::Player(const Player &p)
{
    this->name = p.name;
}

Player::Player(std::string pName)
{
    this->name = pName;
}

Player::Player(const Player &p, string pName)
{
    for (auto it = p.terrs.begin(); it != p.terrs.end(); ++it)
    {
        this->terrs.push_back(*it);
    }
    this->name = pName;
}

Player &Player::operator=(const Player &p)
{
    Player *p1 = new Player(p);
    Player &pCopy = *p1;
    return pCopy;
}

ostream &operator<<(ostream &out, const Player &p)
{
    out << p.toString();
    out << endl;
    return out;
}

vector<Territory *> Player::toAttack()
{
    // for now only arbitary territory list returned
    vector<Territory *> terrAttack;
    for (vector<Territory *>::iterator it = terrs.begin(); it != terrs.end(); ++it)
    {
        terrAttack.push_back(*it);
    }
    return terrAttack;
}

vector<Territory *> Player::toDefend()
{
    // for now only arbitary territory list returned
    vector<Territory *> terrDefend;
    for (vector<Territory *>::iterator it = terrs.begin(); it != terrs.end(); ++it)
    {
        terrDefend.push_back(*it);
    }
    return terrDefend;
}

void Player::issueOrder(string)
{
    Order *ord = new Order();
    orders.push_back(ord);
}

string Player::toString() const
{
    string pInfo = "";
    pInfo += "Player " + this->getName() + "\'s info: \n";
    pInfo += "\tTerritory owned: \n";
    for (auto it = this->terrs.begin(); it != this->terrs.end(); ++it)
    {
        pInfo += (*it)->getName() + ", ";
    }
    pInfo += "\n\tCards owned: \n";
    for (auto it = this->cards.begin(); it != this->cards.end(); ++it)
    {
        pInfo += (*it)->getType() + ", ";
    }
    pInfo += "\n";
    return pInfo;
}

string Player::getName() const
{
    return name;
}

vector<Territory*> Player::getTerritories() {
    return terrs;
}

void Player::addTerritory(Territory *territory) {
    territory->setOwner(this);
    this->terrs.push_back(territory);
}

int* Player::getArmies() {
    return armies;
}
void Player::addArmies(int armies) {
    *this->armies+=armies;
}

bool Player::isOwner(Continent *continent){
    vector<Territory*> ownedTerrs;
    for(int i=0; i<terrs.size();i++){
        if(terrs[i]->getContinent()==continent){
            ownedTerrs.push_back(terrs[i]);
        }
    }
    if(ownedTerrs.size()==continent->getTerritories().size()){
        return true;
    }
    else{
        return false;
    }
}

bool Player::isOwner(Territory *territory) {
    for(int i=0; i<this->terrs.size();i++){
        if(territory==terrs[i]){
            return true;
        }
    }
    return false;
}
