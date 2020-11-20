#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Player;
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
    bool hasOwner();
    void setNeutral();
    friend class Deploy;
    friend class Advance;
    friend class Airlift;
    friend class Bomb;
    friend class Blockade;
    friend class Negotiate;
};

class Continent{
private:
    string* name;
    int* bonus;
    vector<Territory*> territories;
public:
    Continent();
    Continent(string name, int* bonus);
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
    void setBonus(int bonus);
    int getBonus();
};
