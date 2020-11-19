#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine()
{
    //set the state to "startup" initially
    state = "Start up";
    Notify();

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
        this->executeOrderPhase();
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
                cout << "Congratulations! " << players[i]->getName() << " has won the game!" << endl;
                exit(0);
            }
        }
    }
}

void GameEngine::reinforcementPhase()
{
    cout << "---------------------" << endl;
    cout << "Reinforcement phase starts..." << endl;

    state = "Reinforcement Phase";
    Notify();

    for (int i = 0; i < players.size(); i++)
    {
        int terriArmy = players[i]->getTerritories().size() / 3;
        if (terriArmy < 3)
        {
            terriArmy = 3;
        }
        cout << players[i]->getName() << " got " << terriArmy << " armies from owned territories." << endl;
        int conArmy = 0;
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
    state = "Issue Orders Phase";
    Notify();

    cout << "---------------------" << endl;
    cout << "It's time for deploying armies" << endl;
    cout << "" << endl;

    for(int i = 0; i<=players.size();i++) {
        vector<Territory *> v =players[i]->getTerritories();
        cout<<"Here is your territories: " <<endl;
        for(int j = 1; j < v.size(); j++){
            cout << j << ". " << v[j-1]->getName() << " ";
        }
        cout << "" << endl;

        while (players[i]->getArmies() != 0) {
            int cTerr;
            int numberOfArmies = 0;
            cout << "Please choose a territory you owned for placing armies(using the number in front of territory): " << endl;
            cin >> cTerr;
            if(players[i]->isOwner(reinterpret_cast<Territory *>(cTerr))){//not sure with the function
                cout << "How many armies you want to place in this territory?" << endl;
                cout<<"You still have "<< players[i]->getArmies() << " left. "<< endl;
                cin >> numberOfArmies;
                *players[i]->getTerritories()[cTerr]->getNumberOfArmies()+=numberOfArmies;
            }
            else{
                cout<<"Please enter a valid choice!"<<endl;
            }
        }
    }

    cout << "---------------------" << endl;
    cout << "It's time for placing orders" << endl;
    cout << "" << endl;

    for(int i = 0; i<players.size();i++){
        vector<Territory *> v =players[i]->getTerritories();
        cout<<"Moving to a new player..." << endl;
        cout<<players[i]->getName()<<"'s term!" << endl;
        cout << "" << endl;

        while(true){
            int answer;
            cout<<"Do you want to issue a new order?(using the number in front)"<<endl;
            cout << "1. yes" << endl;
            cout << "2. no" << endl;
            cout << "3. I would like to use a card!" << endl;
            cin>>answer;
            if(answer == 1){
                int st;
                int sd;
                cout<<"Here is your territories: " <<endl;
                for(int j = 1; j < v.size(); j++){
                    cout << j << ". " << v[j-1]->getName() << " ";
                }
                cout << "" << endl;
                cout << "Please choose a territory you owned for placing order(using the number in front of territory): " << endl;
                cin>>st;
                cout<<"What are you gonna do?(using the number in front)"<<endl;
                cout<<"1. attack"<<endl;
                cout<<"2. defend"<<endl;
                cin>>sd;
                if(sd = 1){
                    int territoryAttackTarget;
                    int armiesNumber;
                    cout<<"Here is your neighbour of this territory: " <<endl;
                    for(int j = 1; j < v[st-1]->getNeighbours().size(); j++){
                        cout << j << ". " << v[st-1]->getNeighbours()[j-1]->getName()<< " ";
                    }
                    cout << "" << endl;
                    cout<<"Choose a territory to attack(You can only choose your neighbour)(using number):"<<endl;
                    cin>>territoryAttackTarget;
                    cout<<"How many armies you want to use?"<<endl;
                    cin>>armiesNumber;
                    players[i]->issueOrder("attack", v[st-1]->getName(), v[st-1]->getNeighbours()[territoryAttackTarget-1]->getName(), armiesNumber);
                }
                else if(sd = 2){
                    int territoryAttackTarget;
                    int armiesNumber;
                    cout<<"Here is your neighbour of this territory: " <<endl;
                    for(int j = 1; j < v[st-1]->getNeighbours().size(); j++){
                        cout << j << ". " << v[st-1]->getNeighbours()[j-1]->getName()<< " ";
                    }
                    cout << "" << endl;
                    cout<<"Choose a territory to defend(You can only choose your neighbour)(using number):"<<endl;
                    cin>>territoryAttackTarget;
                    cout<<"How many armies you want to move?"<<endl;
                    cin>>armiesNumber;
                    players[i]->issueOrder("defend", v[st-1]->getName(), v[st-1]->getNeighbours()[territoryAttackTarget-1]->getName(), armiesNumber);
                }
                else{
                    cout<<"Please enter a valid choice!"<<endl;
                }


                /*cout<<"Please choose to defend or attack(Type defend or attack): "<<endl;
                cin>>cDA;
                if(cDA == "defend"){
                    string target;
                    cout<<"Here is your territories: " <<endl;
                    for(int i; i<players[i]->getTerritories().size(); i++){
                        cout << i << ". " << players[i]->getTerritories()[i]->getName() << " ";
                    }
                    cout << "" << endl;
                    cout<<"Please enter a territory you want to defend(you can only defend the territory you owned): "<<endl;
                    cin>>target;

                    players[i]->issueOrder(cDA, target);
                }else if(cDA == "attack"){

                }
                else{
                    cout<<"Please enter a valid choice!"<<endl;
                    cout<<""<<endl;
                }*/
            }
            else if(answer == 3){
            }
            else if(answer == 2 )
                break;
            else{
                cout<<"Please enter a valid choice!"<<endl;
            }
        }
    }
    cout << "---------------------" << endl;
    cout << "" << endl;
}

void GameEngine::executeOrderPhase()
{

    state = "Execute Orders Phase";
    Notify();

    cout << "---------------------" << endl;
    cout << "It's time for execute orders!" << endl;
    cout << "" << endl;

    Order(OrderList).execute();
}

string GameEngine::getState(){

}

