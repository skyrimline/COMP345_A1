#include "Map.h"
#include <vector>
#include <iostream>
using namespace std;

Map::Map() {}

Map::Map(Map *map) {
    this->continents=map->continents;
    this->territories=map->territories;
}

Map::~Map() {}

vector<Continent*> Map::getContinents() {
    return this->continents;
}

vector<Territory*> Map::getTerritories() {
    return this->territories;
}

Continent* Map::getContinentByIndex(int indexOfContinent, vector<string> continentsList){
    Continent* temp = new Continent(continentsList[indexOfContinent]);
    return temp;
}

Territory* Map::getTerritoryByIndex(int indexOfTerritory, vector<string> territoryList) {
    Territory* temp = new Territory(territoryList[indexOfTerritory]);
    return temp;
}

void Map::addContinent(Continent *continent) {
    this->continents.push_back(continent);
}

void Map::addTerritory(Territory *territory) {
    this->territories.push_back(territory);
}

bool Map::isConnectedGraph() {
    bool visited [this->territories.size()];
    for (int i=0; i<this->territories.size(); i++){
        visited[i]=false;
    }
    vector<Territory*> visit;
    visit.push_back(this->territories[0]);
    visited[0]=1;
    while(visit.size()!=0){
        vector<Territory*> neighbours=visit.front()->getNeighbours();
        visit.insert(visit.end(), neighbours.begin(), neighbours.end());
        for(int i=0; i<neighbours.size(); i++){
            bool containFlag=false;
            bool checkedFlag=false;
            for(int j=0; j<neighbours.size(); j++){
                if(neighbours[i]==neighbours[j]){
                    containFlag=true;
                }
            }
            for(int j=0; j<this->territories.size(); j++){
                if(neighbours[i]==territories[j]){
                    checkedFlag==visited[j];
                }
                visited[j]=true;
            }
            if(!containFlag&&!checkedFlag){
                visit.push_back(neighbours[i]);
            }
        }
        visit.erase(visit.begin());
    }
    for (int i=0; i<this->territories.size(); i++){
        if(!visited[i]){
            return false;
        }
    }
    return true;
}

bool Map::validate() {
    //checks if the map is a connected graph
    bool mapFlag=this->isConnectedGraph();
    //checks if the continents are connected graphs
    bool continentsFlag=true;
    for(int i=0; i<this->continents.size(); i++){
        if(!continents[i]->isConnectedGraph()){
            continentsFlag=false;
            break;
        }
    }
    //checks if every territory belongs to one continent
    bool belongFlag=true;
    for(int i=0; i<this->territories.size(); i++){
        if(territories[i]->getContinent() == NULL){
            belongFlag=false;
            break;
        }
        if(!territories[i]->getContinent()->contains(territories[i])){
            belongFlag=false;
            break;
        }
    }
    //checks if each territory belongs to only one continent
    bool uniqueFlag=true;
    vector<Territory*> allTerritories;
    for(int i=0; i<this->continents.size();i++){
        allTerritories.insert(allTerritories.end(), this->continents[i]->getTerritories().begin(), this->continents[i]->getTerritories().end());
    }
    if(allTerritories.size()!=this->territories.size()){
        uniqueFlag=false;
    }
    return mapFlag&&continentsFlag&&uniqueFlag&&belongFlag;
}


void Map::print() {
    cout<<"Information for the map:"<<endl;
    for(int i=0; i<this->continents.size(); i++){
        this->continents[i]->print();
    }
}

Territory::Territory() {}

Territory::Territory(string name) {
    this->name = new string(name);
}

Territory::Territory(string name, Continent *continent) {
    this->name=new string(name);
    this->setContinent(continent);
    continent->addTerritory(this);
}

Territory::Territory(Territory *territory) {
    this->name=territory->name;
    this->continent=territory->continent;
    this->neighbours=territory->neighbours;
    this->owner=territory->owner;
    this->numberOfArmies=territory->numberOfArmies;
}

Territory::~Territory() {}

string Territory::getName() {
    return *name;
}

int Territory::getNumberOfArmies() {
    return numberOfArmies;
}

Player Territory::getOwner() {
    return *owner;
}

Continent* Territory::getContinent() {
    return continent;
}

vector<Territory*> Territory::getNeighbours() {
    return neighbours;
}

void Territory::setNumberOfArmies(int numberOfArmies) {
    this->numberOfArmies=numberOfArmies;
}

void Territory::setOwner(Player *owner) {
    Player* oldOwner=this->owner;
    this->owner=owner;
    delete oldOwner;
}

void Territory::setName(string name) {
    string* oldName=this->name;
    this->name=new string(name);
    delete oldName;
}

void Territory::setContinent(Continent *continent) {
    Continent* oldContinent=this->continent;
    oldContinent->deleteTerritory(this);
    this->continent=continent;
    continent->addTerritory(this);
}

void Territory::addNeighbour(Territory *neighbour) {
    this->neighbours.push_back(neighbour);
}

Continent::Continent() {}

Continent::Continent(string name) {
    this->name=new string(name);
}

Continent::Continent(Continent *continent) {
    this->name=continent->name;
    this->territories=continent->territories;
}

Continent::~Continent() {}

string Continent::getName() {
    return *name;
}

vector<Territory*> Continent::getTerritories() {
    return territories;
}

void Continent::setName(string name) {
    string* oldName=this->name;
    this->name=new string(name);
    delete oldName;
}

void Continent::addTerritory(Territory* territory) {
    territory->setContinent(this);
    this->territories.push_back(territory);
}

void Continent::deleteTerritory(Territory *territory) {
    for(int i=0; i<this->territories.size(); i++){
        if(territories[i]->getName()==territory->getName()){
            this->territories.erase(territories.begin()+i);
        }
    }
}

bool Continent::isConnectedGraph() {
    bool visited [this->territories.size()];
    for (int i=0; i<this->territories.size(); i++){
        visited[i]=false;
    }
    vector<Territory*> visit;
    visit.push_back(this->territories[0]);
    visited[0]=1;
    while(visit.size()!=0){
        vector<Territory*> neighbours=visit.front()->getNeighbours();
        visit.insert(visit.end(), neighbours.begin(), neighbours.end());
        for(int i=0; i<neighbours.size(); i++){
            bool containFlag=false;
            bool checkedFlag=false;
            for(int j=0; j<neighbours.size(); j++){
                if(neighbours[i]==neighbours[j]){
                    containFlag=true;
                }
            }
            for(int j=0; j<this->territories.size(); j++){
                if(neighbours[i]==territories[j]){
                    checkedFlag==visited[j];
                }
                visited[j]=true;
            }
            if(!containFlag&&!checkedFlag){
                visit.push_back(neighbours[i]);
            }
        }
        visit.erase(visit.begin());
    }
    for (int i=0; i<this->territories.size(); i++){
        if(!visited[i]){
            return false;
        }
    }
    return true;
}

bool Continent::contains(Territory *territory) {
    for(int i=0; i<territories.size(); i++){
        if(territories[i]==territory-){
            return true;
        }
    }
    return false;
}

void Continent::print() {
    cout<<"Territories in "<<this->name<<":"<<endl;
    for (int i=0; i<this->territories.size(); i++){
        cout<<"  "<<this->territories[i]->getName()<<endl;
    }
}