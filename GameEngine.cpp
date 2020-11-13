#include "GameEngine.h"
#include "Map.h"
#include "MapLoader.h"
#include <random>
#include <fstream>
#include <iostream>
using namespace std;

GameEngine::GameEngine()
{
    // define array for candidate maps
    static string mapName[] = {"artic", "austria-hungary", "canada", "solar"};

    // randomly select a map to open
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, 3);
    int mapId = distribution(generator);
    string mapFileName = "./Map/" + mapName[mapId] + ".map";

    // use Maploader to load selected map
    MapLoader *ml = new MapLoader();
    gameMap = &ml->readMap(mapFileName);

    // verify the connectivity of selected map
    bool isConnected = gameMap->isConnectedGraph();
    if (!isConnected)
    {
        cout << "Selected map is not a connected graph." << endl;
        cout << "Restart the game to choose another valid map" << endl;
        exit(0);
    }

    // create 2-5 players
    string playerName[]{"Jason", "Stanley", "Aaron", "John", "Benjarmin"};
    uniform_int_distribution<int> distribution(2, 5);
    int numOfPlayer = distribution(generator);
    for (int i = 0; i < numOfPlayer; ++i)
    {
        players[i] = new Player(playerName[i]);
    }

    // create a deck of cards
    // to be continued
}