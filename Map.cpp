#include "Map.h"
#include "Player.h"
#include <vector>
#include <iostream>

using namespace std;

Map::Map() {}

Map::Map(Map *map) {
    this->continents = map->continents;
    this->territories = map->territories;
}

Map::~Map() {}

vector<Continent *> Map::getContinents() {
    return this->continents;
}

vector<Territory *> Map::getTerritories() {
    return this->territories;
}

void Map::addContinent(Continent *continent) {
    this->continents.push_back(continent);
    for (int i = 0; i < continent->getTerritories().size(); i++) {
        this->territories.push_back(continent->getTerritories()[i]);
    }
}

void Map::addTerritory(Territory *territory) {
    this->territories.push_back(territory);
}

bool Map::isConnectedGraph() {
    //used to record if a territory is visited
    vector<bool> visited;
    for (int i = 0; i < this->territories.size(); i++) {
        visited.push_back(false);
    }
    //a queue for territories that are waiting to be visited
    vector<Territory *> visit;
    //put the first territory into the queue
    visit.push_back(this->territories[0]);
    while (visit.size() != 0) {
        Territory *current = visit.front();
        vector<Territory *> neighbours = current->getNeighbours();
        for (int i = 0; i < neighbours.size(); i++) {
            Territory *currentNeighbour = neighbours[i];
            bool containFlag = false;
            bool checkedFlag = false;
            //check if the current neighbour is already in the queue
            for (int j = 0; j < visit.size(); j++) {
                if (currentNeighbour == visit[j]) {
                    containFlag = true;
                    break;
                }
            }
            //check if the current neighbour is already visited
            for (int j = 0; j < this->territories.size(); j++) {
                if (currentNeighbour == territories[j]) {
                    checkedFlag = visited[j];
                    break;
                }
            }
            //if the current neighbour is neither in the queue nor visited, put it into the queue
            if (!containFlag && !checkedFlag) {
                visit.push_back(currentNeighbour);

            }
        }
        //mark the status of current territory "visited"
        for (int j = 0; j < this->territories.size(); j++) {
            if (current == territories[j]) {
                visited[j] = true;
                break;
            }
        }
        visit.erase(visit.begin());
    }
    //if not all the territories are visited, return false
    for (int i = 0; i < this->territories.size(); i++) {
        if (!visited[i]) {
            return false;
        }
    }
    return true;
}

bool Map::validate() {
    //checks if the map is a connected graph
    bool mapFlag = this->isConnectedGraph();
    //checks if the continents are connected graphs
    bool continentsFlag = true;
    for (int i = 0; i < this->continents.size(); i++) {
        if (!continents[i]->isConnectedGraph()) {
            continentsFlag = false;
            break;
        }
    }
    //checks if every territory belongs to one continent
    bool belongFlag = true;
    for (int i = 0; i < this->territories.size(); i++) {
        if (territories[i]->getContinent() == NULL) {
            belongFlag = false;
            break;
        }
        if (!territories[i]->getContinent()->contains(territories[i])) {
            belongFlag = false;
            break;
        }
    }
    //checks if each territory belongs to only one continent
    bool uniqueFlag = true;
    int allTerritories = 0;
    for (int i = 0; i < this->continents.size(); i++) {
        allTerritories += this->continents[i]->getTerritories().size();
    }
    if (allTerritories != this->territories.size()) {
        uniqueFlag = false;
    }
    return mapFlag && continentsFlag && uniqueFlag && belongFlag;
}


void Map::print() {
    cout << "Information for the map:" << endl;
    for (int i = 0; i < this->continents.size(); i++) {
        this->continents[i]->print();
    }
}

Territory::Territory() {}

Territory::Territory(string name) {
    this->name = new string(name);
}

Territory::Territory(string name, Continent *continent) {
    this->name = new string(name);
    this->continent = continent;
    continent->addTerritory(this);
}

Territory::Territory(Territory *territory) {
    this->name = territory->name;
    this->continent = territory->continent;
    this->neighbours = territory->neighbours;
    this->owner = territory->owner;
    this->numberOfArmies = territory->numberOfArmies;
}

Territory::~Territory() {}

string Territory::getName() {
    return *name;
}

int* Territory::getNumberOfArmies() {
    return numberOfArmies;
}

Player Territory::getOwner() {
    return *owner;
}

Continent *Territory::getContinent() {
    return continent;
}

vector<Territory *> Territory::getNeighbours() {
    return neighbours;
}

void Territory::setNumberOfArmies(int numberOfArmies) {
    this->numberOfArmies = new int(numberOfArmies);
}

void Territory::setOwner(Player *owner) {
    this->owner = owner;
}

void Territory::setName(string name) {
    string *oldName = this->name;
    this->name = new string(name);
    delete oldName;
}

void Territory::setContinent(Continent *continent) {
    Continent *oldContinent = this->continent;
    if (oldContinent != NULL) {
        oldContinent->deleteTerritory(this);
    }
    this->continent = continent;
    continent->addTerritory(this);
}

void Territory::addNeighbour(Territory *neighbour) {
    if (!this->isNeighbour(neighbour)) {
        this->neighbours.push_back(neighbour);
    }
    if (!neighbour->isNeighbour(this)) {
        neighbour->neighbours.push_back(this);
    }
}

bool Territory::isNeighbour(Territory *neighbour) {
    for (int i = 0; i < this->getNeighbours().size(); i++) {
        if (this->getNeighbours()[i] == neighbour) {
            return true;
        }
    }
    return false;
}

bool Territory::hasOwner() {
    if(this->owner==NULL){
        return false;
    }
    else{
        return true;
    }
}

Continent::Continent() {}

Continent::Continent(string name, int bonus) {
    this->name = new string(name);
    this->bonus = new int(bonus);
}

Continent::Continent(Continent *continent) {
    this->name = continent->name;
    this->territories = continent->territories;
}

Continent::~Continent() {}

string Continent::getName() {
    return *name;
}

vector<Territory *> Continent::getTerritories() {
    return territories;
}

void Continent::setName(string name) {
    string *oldName = this->name;
    this->name = new string(name);
    delete oldName;
}

void Continent::addTerritory(Territory *territory) {
    if (territory->getContinent() != this) {
        territory->setContinent(this);
    } else {
        this->territories.push_back(territory);
    }
}

void Continent::deleteTerritory(Territory *territory) {
    for (int i = 0; i < this->territories.size(); i++) {
        if (territories[i]->getName() == territory->getName()) {
            this->territories.erase(territories.begin() + i);
        }
    }
}

bool Continent::isConnectedGraph() {
    vector<bool> visited;
    for (int i = 0; i < this->territories.size(); i++) {
        visited.push_back(false);
    }
    vector<Territory *> visit;
    visit.push_back(this->territories[0]);
    while (visit.size() != 0) {
        Territory *current = visit.front();
        vector<Territory *> neighbours = current->getNeighbours();
        for (int i = 0; i < neighbours.size(); i++) {
            Territory *currentNeighbour = neighbours[i];
            bool containFlag = false;
            bool checkedFlag = false;
            bool localFlag = false;
            //check if the current neighbour is on the same continent with current territory
            //if not, ignore it
            if (currentNeighbour->getContinent() == visit.front()->getContinent()) {
                localFlag = true;
                for (int j = 0; j < visit.size(); j++) {
                    if (currentNeighbour == visit[j]) {
                        containFlag = true;
                        break;
                    }
                }
                for (int j = 0; j < this->territories.size(); j++) {
                    if (currentNeighbour == territories[j]) {
                        checkedFlag = visited[j];
                        break;
                    }
                }
            }
            if (!containFlag && !checkedFlag && localFlag) {
                visit.push_back(currentNeighbour);
            }
        }
        for (int j = 0; j < this->territories.size(); j++) {
            if (current == territories[j]) {
                visited[j] = true;
                break;
            }
        }
        visit.erase(visit.begin());
    }
    for (int i = 0; i < this->territories.size(); i++) {
        if (!visited[i]) {
            return false;
        }
    }
    return true;
}

bool Continent::contains(Territory *territory) {
    for (int i = 0; i < territories.size(); i++) {
        if (territories[i] == territory) {
            return true;
        }
    }
    return false;
}

void Continent::print() {
    cout << "Territories in " << *(this->name) << ":" << endl;
    for (int i = 0; i < this->territories.size(); i++) {
        cout << "  " << i + 1 << ". " << this->territories[i]->getName() << endl;
    }
    cout<<"The bonus value for this continent is: "<<bonus<<endl;
}

void Continent::setBonus(int bonus) {
    *this->bonus=bonus;
}

int Continent::getBonus() {
    return *bonus;
}
