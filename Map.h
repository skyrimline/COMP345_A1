#pragma once
#include <iostream>
#include <vector>
#include "Player.h"
using namespace std;

class Territory;
class Continent;

class Map {
private:
    vector<Continent*> continents;
    vector<Territory*> territories;
public:
    Map();
    Map(Map* map);
    ~Map();
    vector<Continent*> getContinents();
    vector<Territory*> getTerritories();
    void addContinent(Continent* continent);
    void addTerritory(Territory* territory);
    void print();
    bool isConnectedGraph();
    bool validate();
};

class Territory{
private:
    string* name;
    Player* owner;
    vector<Territory*> neighbours;
    int* numberOfArmies;
    Continent* continent;
public:
    Territory();
    Territory(string name);
    Territory(string name, Continent* continent);
    Territory(Territory* territory);
    ~Territory();
    string getName();
    Player getOwner();
    vector<Territory*> getNeighbours();
    int* getNumberOfArmies();
    Continent* getContinent();
    void setName(string name);
    void setOwner(Player* owner);
    void setNumberOfArmies(int numberOfArmies);
    void setContinent(Continent* continent);
    void addNeighbour(Territory* neighbour);
    bool isNeighbour(Territory* neighbour);
};

class Continent{
private:
    string* name;
    vector<Territory*> territories;
public:
    Continent();
    Continent(string name);
    Continent(Continent* continent);
    ~Continent();
    string getName();
    vector<Territory*> getTerritories();
    void setName(string name);
    void addTerritory(Territory* territory);
    void deleteTerritory(Territory* territory);
    bool isConnectedGraph();
    bool contains(Territory* territory);
    void print();
};
