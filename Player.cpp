#include "Player.h"
#include <vector>
using namespace std;

Subject::Subject() {
    _observers = new list<Observer*>;
}

Subject::~Subject() {
    delete _observers;
}

void Subject::Attach(Observer* o) {
    _observers->push_back(o);
};

void Subject::Detach(Observer* o) {
    _observers->remove(o);
};

void Subject::Notify() {
    list<Observer*>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i)
        (*i)->Update();
};

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
    vector<Territory *> terrAttack;
    cout<<"Please choose the countries you would like to attack:"<<endl;
    for(int i=1;i<=this->terrs.size();i++){
        cout<<i<<". "<<this->terrs[i]->getName()<<endl;
    }
    cout<<this->terrs.size()<<". Exit"<<endl;
    bool firstFlag=true;
    int firstIndex;
    cin>>firstIndex;
    while(firstFlag) {
        if (firstIndex == this->terrs.size()) {
            cout << "You have to choose at least one territory! Please enter another number:" << endl;
        } else if (firstIndex > this->terrs.size()) {
            cout << "Please enter a valid number!" << endl;
        } else {
            terrAttack.push_back(this->terrs[firstIndex]);
            firstFlag = false;
        }
    }
    int attackIndex;
    while(attackIndex!=this->terrs.size()){
        cin>>attackIndex;
        if(attackIndex!=this->terrs.size()){
            terrAttack.push_back(this->terrs[attackIndex]);
        }
        else if (attackIndex > this->terrs.size()) {
            cout << "Please enter a valid number!" << endl;
        }
    }
    return terrAttack;
}

vector<Territory *> Player::toDefend()
{
    vector<Territory *> terrDefend;
    cout<<"Please choose the countries you would like to defend:"<<endl;
    for(int i=1;i<=this->terrs.size();i++){
        cout<<i<<". "<<this->terrs[i]->getName()<<endl;
    }
    cout<<this->terrs.size()<<". Exit"<<endl;
    bool firstFlag=true;
    int firstIndex;
    cin>>firstIndex;
    while(firstFlag) {
        if (firstIndex == this->terrs.size()) {
            cout << "You have to choose at least one territory! Please enter another number:" << endl;
        } else if (firstIndex > this->terrs.size()) {
            cout << "Please enter a valid number!" << endl;
        } else {
            terrDefend.push_back(this->terrs[firstIndex]);
            firstFlag = false;
        }
    }
    int defendIndex;
    while(defendIndex!=this->terrs.size()){
        cin>>defendIndex;
        if(defendIndex!=this->terrs.size()){
            terrDefend.push_back(this->terrs[defendIndex]);
        }
        else if (defendIndex > this->terrs.size()) {
            cout << "Please enter a valid number!" << endl;
        }
    }
    return terrDefend;
}

void Player::issueOrder(string s, Territory* territory, int numOfArmies)
{
    if(s=="deploy"){
        Deploy *deploy = new Deploy(this, territory, numOfArmies);
        orders.push_back(deploy);
    }
}

void Player::issueOrder(string s, Territory * source, Territory * target, int numOfArmies) {
    if(s=="airlift"){
        Airlift *airlift = new Airlift(this, source, target, numOfArmies);
        this->getOrders().push_back(airlift);
    }
}

void Player::issueOrder(string s, Territory * t) {
    if(s=="blockade"){
        Blockade *blockade = new Blockade(this, t);
        this->getOrders().push_back(blockade);
    }
    else if(s=="bomb"){
        Bomb *bomb=new Bomb(this, t);
        this->getOrders().push_back(bomb);
    }
}

void Player::issueOrder(string s, Player * p) {
    if(s=="diplomacy"){
        Negotiate *negotiate = new Negotiate(this, p);
        this->getOrders().push_back(negotiate);
    }
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
    for (auto it = this->hand->getCardsVector().begin(); it != this->hand->getCardsVector().end(); ++it)
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

void Player::addCards(Hand* hand)
{
    vector<Card*> tempCardsVector = hand->getCardsVector();
    while (!tempCardsVector.empty()) {
        Card* tempCard = tempCardsVector.back();
        tempCardsVector.pop_back();
        hand->getCardsVector().push_back(tempCard);
    }
    
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

vector<Order *> Player::getOrders() {
    return orders;
}

Hand* Player::getHand() {
    return hand;
}

void Player::setHand(Hand* hand) {
    this->hand=hand;
}

