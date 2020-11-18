#include "GameEngine.h"

GameEngine::GameEngine()
{
    // define array for candidate maps
    static const string mapName[] = {"artic", "austria-hungary", "canada", "solar"};

    // randomly select a map to open
    default_random_engine generator;
    uniform_int_distribution<int> distribution1(0, 3);
    int mapId = distribution1(generator);
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
    uniform_int_distribution<int> distribution2(2, 5);
    int numOfPlayer = distribution2(generator);
    for (int i = 0; i < numOfPlayer; ++i)
    {
        players[i] = new Player(playerName[i]);
    }

    // create a deck of cards, assign it to each player
    for (int i = 0; i < numOfPlayer; ++i)
    {
        cards[i] = new Hand();
        players[i]->addCards(cards[i]);
    }
}

void GameEngine::startupPhase()
{
    //decide the order of play
    for (int i = 0; i < players.size() * 10; i++)
    {
        int randomNum1 = rand() % players.size();
        int randomNum2 = rand() % players.size();
        Player temp = *players[randomNum1];
        *players[randomNum1] = *players[randomNum2];
        *players[randomNum2] = temp;
    }
    cout << "---------------------" << endl;
    cout << "The order of play is:" << endl;
    for (int i = 0; i < players.size(); i++)
    {
        cout << i << " " << players[i] << endl;
    }
    //randomly assign territories
    cout << "---------------------" << endl;
    cout << "Randomly assigning territories..." << endl;
    int numOfTerri;
    bool luckyFlag;
    if (gameMap->getTerritories().size() % players.size() != 0)
    {
        numOfTerri = gameMap->getTerritories().size() / players.size() + 1;
        luckyFlag = true;
    }
    else
    {
        numOfTerri = gameMap->getTerritories().size() / players.size();
        luckyFlag = false;
    }
    for (int i = 0; i < gameMap->getTerritories().size(); i++)
    {
        int indexOfOwner;
        while (!gameMap->getTerritories()[i]->hasOwner())
        {
            indexOfOwner = rand() % players.size();
            if (players[indexOfOwner]->getTerritories().size() < numOfTerri)
            {
                gameMap->getTerritories()[i]->setOwner(players[indexOfOwner]);
            }
        }
    }
    for (int i = 0; i < players.size(); i++)
    {
        cout << "Player " << i << ":" << endl;
        for (int j = 0; j < players[i]->getTerritories().size(); j++)
        {
            cout << "  " << j << " " << players[i]->getTerritories()[j]->getName() << endl;
        }
        if (luckyFlag && players[i]->getTerritories().size() > numOfTerri)
        {
            cout << "You are lucky! You have got one more territory than the others!" << endl;
        }
        if (i < players.size())
        {
            cout << endl;
        }
    }
    //give initial armies
    cout << "---------------------" << endl;
    int numOfIniArmies;
    switch (players.size())
    {
    case 2:
        numOfIniArmies = 40;
        break;

    case 3:
        numOfIniArmies = 35;
        break;

    case 4:
        numOfIniArmies = 30;
        break;

    case 5:
        numOfIniArmies = 25;
        break;
    }
    cout << "Number of initial Armies: " << numOfIniArmies << endl;
    for (int i = 0; i < players.size(); i++)
    {
        *players[i]->getArmies() += numOfIniArmies;
    }
}

void GameEngine::mainGameLoop()
{
    while (true)
    {
        this->reinforcementPhase();
        this->issueOrderPhase();
        this->exeuteOrderPhase();
        //check if a player owns no territories
        for (int i = 0; i < players.size(); i++)
        {
            if (players[i]->getTerritories().size() == 0)
            {
                cout << players[i]->getName() << " has no territories left and is removed from the game!" << endl;
                players.erase(players.begin() + i);
            }
        }
        //checks if a player has won the game
        for (int i = 0; i < players.size(); i++)
        {
            if (players[i]->getTerritories().size() == this->gameMap->getTerritories().size())
            {
                cout << "Conguatulations! " << players[i]->getName() << " has won the game!" << endl;
                exit(0);
            }
        }
    }
}

void GameEngine::reinforcementPhase()
{
    cout << "---------------------" << endl;
    cout << "Reinforcement phase starts..." << endl;
    for (int i = 0; i < players.size(); i++)
    {
        int terriArmy = players[i]->getTerritories().size() / 3;
        if (terriArmy < 3)
        {
            terriArmy = 3;
        }
        cout << players[i]->getName() << " got " << terriArmy << " armies from owned territories." << endl;
        int conArmy;
        for (int j = 0; j < gameMap->getContinents().size(); j++)
        {
            if (players[i]->isOwner(gameMap->getContinents()[j]))
            {
                conArmy += gameMap->getContinents()[j]->getBonus();
            }
        }
        cout << players[i]->getName() << " got " << conArmy << " armies from owned continents." << endl;
        players[i]->addArmies(terriArmy + conArmy);
        cout << "Total: " << terriArmy + conArmy << endl;
    }
    cout << "Reinforcement phase ends..." << endl;
    cout << "---------------------" << endl;
}

void GameEngine::issueOrderPhase()
{
}

void GameEngine::exeuteOrderPhase()
{
}