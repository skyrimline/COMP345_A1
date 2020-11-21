#include "GameEngine.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

GameEngine::GameEngine()
{
    // define array for candidate maps
    static const string mapName[] = {"artic", "austria-hungary", "solar"};

    // randomly select a map to open
    gameMap= nullptr;
    MapLoader *ml = new MapLoader();
    while(gameMap==nullptr){
        int mapId=0;
        while(mapId<1||mapId>4) {
            cout << "Please select a map from the list:" << endl;
            cout << "1. Artic" << endl;
            cout << "2. Austria-Hungary" << endl;
            cout << "3. Solar" << endl;
            cin >> mapId;
            if(mapId<1||mapId>3){
                cout<<"Please enter a valid number!"<<endl;
            }
        }
        string mapFileName = "/Users/yunwei/Desktop/Warzone/Map/" + mapName[mapId-1] + ".map";
        // use Maploader to load selected map
        gameMap = ml->readMap(mapFileName);
    }

    // create a deck of cards and display
    cout<<"--------------"<<endl;
    deck=new Deck();
    cout<<"Deck created:"<<endl;
    for(Card* c:deck->getCards()){
        cout<<*c;
    }
    cout<<"--------------"<<endl;


    // create 2-5 players
    int numOfPlayer=0;
    while(numOfPlayer<2||numOfPlayer>5) {
        cout << "Please enter the number of players (2-5):" << endl;
        cin >> numOfPlayer;
        if(numOfPlayer<2||numOfPlayer>5){
            cout<<"Please enter a valid number!"<<endl;
        }
    }
    for (int i = 0; i < numOfPlayer; ++i)
    {
        string name;
        cout<<"Please enter a name for Player"<<i+1<<":"<<endl;
        cin>>name;
        players.push_back( new Player(name));
        players[i]->setHand(new Hand(players[i],deck));
    }
}

void GameEngine::startupPhase()
{
    //decide the order of play
    shuffle(players.begin(), players.end(), std::mt19937(std::random_device()()));
    cout << "---------------------" << endl;
    cout << "The order of play is:" << endl;
    for (int i = 0; i < players.size(); i++)
    {
        cout << i+1 << " " << players[i]->getName() << endl;
    }
    //randomly assign territories
    cout << "---------------------" << endl;
    cout << "Randomly assigning territories..." << endl;
    int numOfTerri;
    bool luckyFlag;
    //check if each players can get equal number of territories
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
                players[indexOfOwner]->addTerritory(gameMap->getTerritories()[i]);
            }
        }
    }
    for (int i = 0; i < players.size(); i++)
    {
        cout << players[i]->getName() << ":" << endl;
        for (int j = 0; j < players[i]->getTerritories().size(); j++)
        {
            cout << "  " << j +1<< " " << players[i]->getTerritories()[j]->getName() << endl;
        }
        if (luckyFlag && players[i]->getTerritories().size() > numOfTerri-1)
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
        players[i]->addArmies(numOfIniArmies);
    }
}

void GameEngine::mainGameLoop()
{
    while (true)
    {
        this->reinforcementPhase();
        this->issueOrderPhase(1);
        this->executeOrderPhase();
        this->issueOrderPhase(2);
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

//    state = "Reinforcement Phase";
//    Notify();

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
                conArmy += *gameMap->getContinents()[j]->getBonus();
            }
        }
        cout << players[i]->getName() << " got " << conArmy << " armies from owned continents." << endl;
        players[i]->addArmies(terriArmy + conArmy);
        cout << "Total: " << terriArmy + conArmy << endl;
    }
    cout << "Reinforcement phase ends..." << endl;
    cout << "---------------------" << endl;
}

void GameEngine::issueOrderPhase(int a)
{
//    state = "Issue Orders Phase";
//    Notify();

    switch(a) {

        //deploy orders
        case 1:
        cout << "All players need to deploy all their armies in hand first!" << endl;
        for (int i = 0; i < players.size(); i++) {
            cout << players[i]->getName() << ", it's your turn!" << endl;
            cout << "You have " << *players[i]->getArmies() << " spare armies in total." << endl;
            vector<Territory *> defend = players[i]->toDefend();
            while (*players[i]->getArmies() != 0) {
                cout << "Your territories to defend:" << endl;
                for (int j = 1; j <= defend.size(); j++) {
                    cout << j << ". " << defend[j-1]->getName() << endl;
                }
                cout << "You have " << *players[i]->getArmies() << " spare armies left." << endl;
                bool validFlag = false;
                int indexTerritory;
                cout << "Please enter the index of territory you would like to defend:" << endl;
                while (!validFlag) {
                    cin>>indexTerritory;
                    if (indexTerritory > defend.size()||indexTerritory<1) {
                        cout << "Please enter a valid number!" << endl;
                    }else{
                        validFlag = true;
                    }
                }
                int numOfArmies=0;
                cout << "Please enter the number of armies you would like to use:" << endl;
                validFlag = false;
                while (!validFlag) {
                    cin>>numOfArmies;
                    if (numOfArmies > *players[i]->getArmies()||numOfArmies<0) {
                        cout << "Please enter a valid number!" << endl;
                    } else {
                        players[i]->issueOrder("deploy", defend[indexTerritory-1], numOfArmies);
                        validFlag = true;
                    }
                }
            }
        }
        break;

        //other orders
        case 2:
            cout<<"Now it's time to issue other orders!"<<endl;
            for (int i = 0; i < players.size(); i++){
                cout << players[i]->getName() << ", it's your turn!" << endl;

                //use airlift cards
                Card* airlift=players[i]->getHand()->firstAirlift();
                if(airlift== nullptr){
                    cout<<"You do not have any Airlift cards!"<<endl;
                }
                while(airlift!= nullptr){
                    int choice=0;
                    while(choice!=1||choice!=2){
                        cout<<"You have Airlift cards. Would you like to use it?"<<endl;
                        cout<<"1. Yes"<<endl;
                        cout<<"2. No"<<endl;
                        cin>>choice;
                        if(choice<1||choice>2){
                            cout<<"Please enter a valid number!"<<endl;
                        }
                        else{
                            switch(choice){
                                case 1: {
                                    Territory* source;
                                    Territory* target;
                                    do {
                                        int choice1 = 0;
                                        while (choice1 < 1 || choice1 > players[i]->getTerritories().size() ) {
                                            cout << "Please choose a source territory:" << endl;
                                            for (int j = 1; j <= players[i]->getTerritories().size(); j++) {
                                                cout << i << ". " << players[i]->getTerritories()[j]->getName() << endl;
                                            }
                                            cin >> choice1;
                                            if (choice1 < 1 || choice1 > players[i]->getTerritories().size() ) {
                                                cout << "Please enter a valid number!" << endl;
                                            } else {
                                                source = players[i]->getTerritories()[choice1 - 1];
                                            }
                                        }
                                        cout << "Please choose a target territory:" << endl;
                                        int choice2 = 0;
                                        while (choice2 < 1 || choice2 > gameMap->getTerritories().size() ) {
                                            cout << "Please choose a target territory:" << endl;
                                            for (int j = 1; j <= gameMap->getTerritories().size(); j++) {
                                                cout << i << ". " << gameMap->getTerritories()[j]->getName() << endl;
                                            }
                                            cin >> choice2;
                                            if (choice2 < 1 || choice2 > players[i]->getTerritories().size() ) {
                                                cout << "Please enter a valid number!" << endl;
                                            } else {
                                                target = gameMap->getTerritories()[choice2 - 1];
                                            }
                                        }
                                        if(source==target){
                                            cout<<"The source country and the target country cannot be the same! Please choose again!"<<endl;
                                        }
                                    }while(source==target);
                                    int numOfArmies=-1;
                                    while(numOfArmies<0||numOfArmies>*source->getNumberOfArmies()) {
                                        cout << "You have " << *source->getNumberOfArmies()<< " armies in the source country." << endl;
                                        cout << "Please enter the number of armies you would like to transfer:" << endl;
                                        cin >> numOfArmies;
                                        if(numOfArmies<0||numOfArmies>*source->getNumberOfArmies()){
                                            cout<<"Please enter a valid number!"<<endl;
                                        }
                                    }
                                    players[i]->issueOrder("airlift", source, target, numOfArmies);
                                    airlift->play();
                                    airlift=players[i]->getHand()->firstAirlift();
                                    break;
                                }

                                case 2: {
                                    cout << "Got it!" << endl;
                                    break;
                                }
                            }
                        }
                    }
                }

                //use blockade cards
                Card* blockade=players[i]->getHand()->firstBlockade();
                if(blockade== nullptr){
                    cout<<"You do not have any Blockade cards!"<<endl;
                }
                while(blockade != nullptr){
                    int choice=0;
                    while(choice!=1||choice!=2){
                        cout<<"You have Blockade cards. Would you like to use it?"<<endl;
                        cout<<"1. Yes"<<endl;
                        cout<<"2. No"<<endl;
                        cin>>choice;
                        if(choice<1||choice>2){
                            cout<<"Please enter a valid number!"<<endl;
                        }
                        else{
                            switch(choice){
                                case 1: {
                                    int choice=0;
                                    while(choice<1||choice>players[i]->getTerritories().size()){
                                        cout<<"Please choose a territory you would like to use the card on:"<<endl;
                                        for (int j = 1; j <= players[i]->getTerritories().size(); j++) {
                                            cout << i << ". " << players[i]->getTerritories()[j]->getName() << endl;
                                        }
                                        cin >> choice;
                                        if (choice < 1 || choice > players[i]->getTerritories().size()) {
                                            cout << "Please enter a valid number!" << endl;
                                        }
                                    }
                                    players[i]->issueOrder("blockade", players[i]->getTerritories()[choice-1]);
                                    blockade->play();
                                    blockade=players[i]->getHand()->firstBlockade();
                                    break;
                                }

                                case 2: {
                                    cout << "Got it!" << endl;
                                    break;
                                }
                            }
                        }
                    }
                }

                int choice=0;
                while(choice!=3) {
                    cout << "What else would you like to do?" << endl;
                    cout << "1. Advance" << endl;
                    cout << "2. Use other cards" << endl;
                    cout << "3. Exit" << endl;
                    cin>>choice;
                    if(choice<1||choice>3){
                        cout<<"Pleace enter a valid number!"<<endl;
                    }
                    else{
                        switch(choice){
                            //advance
                            case 1: {
                                Territory* source;
                                Territory* target;
                                int choice1 = 0;
                                while (choice1 < 1 || choice1 > players[i]->getTerritories().size() ) {
                                    cout << "Please choose a source territory:" << endl;
                                    for (int j = 1; j <= players[i]->getTerritories().size(); j++) {
                                        cout << j << ". " << players[i]->getTerritories()[j-1]->getName() << endl;
                                    }
                                    cin >> choice1;
                                    if (choice1 < 1 || choice1 > players[i]->getTerritories().size() ) {
                                        cout << "Please enter a valid number!" << endl;
                                    } else {
                                        source = players[i]->getTerritories()[choice1 - 1];
                                    }
                                }
                                int choice2=0;
                                vector<Territory *> terrs;
                                while(choice2!=3) {
                                    cout << "Would you like to defend or attack?" << endl;
                                    cout << "1. Defend" << endl;
                                    cout << "2. Attack" << endl;
                                    cout<<"3. Exit"<<endl;
                                    cin >> choice2;
                                    if (choice2 < 1 || choice2 > 3) {
                                        cout << "Please enter a valid number!" << endl;
                                    }
                                    //choose to defend
                                    else if (choice2 == 1) {
                                        terrs = players[i]->toDefend();
                                        cout << "Please choose a target territory:" << endl;
                                        for (int j = 1; j <= terrs.size(); j++) {
                                            cout << j << ". " << terrs[j-1]->getName() << endl;
                                        }
                                        int choice3 = 0;
                                        while (choice3 < 1 || choice2 > terrs.size() ) {
                                            cin >> choice3;
                                            if (choice3 < 1 || choice3 > terrs.size() ) {
                                                cout << "Please enter a valid number!" << endl;
                                            } else {
                                                target = terrs[choice3 - 1];
                                            }
                                        }
                                        int numOfArmies=-1;
                                        while(numOfArmies<0||numOfArmies>*source->getNumberOfArmies()) {
                                            cout << "You have " << *source->getNumberOfArmies()<< " armies in the source country." << endl;
                                            cout << "Please enter the number of armies you would like to transfer:" << endl;
                                            cin >> numOfArmies;
                                            if(numOfArmies<0||numOfArmies>*source->getNumberOfArmies()){
                                                cout<<"Please enter a valid number!"<<endl;
                                            }
                                        }
                                        players[i]->issueOrder("advance", source, target, numOfArmies);
                                    }
                                    //choose to attack
                                    else if(choice2 == 2){
                                        terrs = players[i]->toAttack(source);
                                        cout << "Please choose a target territory:" << endl;
                                        for (int j = 1; j <= terrs.size(); j++) {
                                            cout << j << ". " << terrs[j-1]->getName() << endl;
                                        }
                                        int choice3 = 0;
                                        while (true) {
                                            cin >> choice3;
                                            if (choice3 < 1 || choice3 > terrs.size() ) {
                                                cout << "Please enter a valid number!" << endl;
                                            } else {
                                                target = terrs[choice3 - 1];
                                                break;
                                            }
                                        }
                                        int numOfArmies=-1;
                                        while(numOfArmies<0||numOfArmies>*source->getNumberOfArmies()) {
                                            cout << "You have " << *source->getNumberOfArmies()<< " armies in the source country." << endl;
                                            cout << "Please enter the number of armies you would like to transfer:" << endl;
                                            cin >> numOfArmies;
                                            if(numOfArmies<0||numOfArmies>*source->getNumberOfArmies()){
                                                cout<<"Please enter a valid number!"<<endl;
                                            }
                                        }
                                        players[i]->issueOrder("advance", source, target, numOfArmies);
                                    }
                                    //exit
                                    else if(choice2 == 3){
                                        cout<<"Got it!"<<endl;
                                    }
                                }
                                break;
                            }

                            //use a card
                            case 2: {
                                int choice=0;
                                while(choice!=4) {
                                    cout << "Please choose from the list:" << endl;
                                    cout << "1. Bomb" << endl;
                                    cout << "2. Reinforcement" << endl;
                                    cout << "3. Diplomacy" << endl;
                                    cout << "4. Return to the upper menu" << endl;
                                    cin >> choice;
                                    if (choice<1||choice>4){
                                        cout<<"Please enter a valid number!"<<endl;
                                    }
                                    else{
                                        switch(choice){

                                            //bomb
                                            case 1:{
                                                Card* bomb=players[i]->getHand()->firstBomb();
                                                if(bomb== nullptr){
                                                    cout<<"You do not have any Bomb cards!"<<endl;
                                                }
                                                else {
                                                    Territory *target;
                                                    cout << "Please choose a target territory:" << endl;
                                                    int choice1 = 0;
                                                    while (choice1 < 1 || choice1 > gameMap->getTerritories().size()) {
                                                        cout << "Please choose a target territory:" << endl;
                                                        for (int j = 1; j <= gameMap->getTerritories().size(); j++) {
                                                            cout << i << ". " << gameMap->getTerritories()[j]->getName()
                                                                 << endl;
                                                        }
                                                        cin >> choice1;
                                                        if (choice1 < 1 ||
                                                            choice1 > players[i]->getTerritories().size()) {
                                                            cout << "Please enter a valid number!" << endl;
                                                        } else {
                                                            target = gameMap->getTerritories()[choice1 - 1];
                                                        }
                                                    }
                                                    players[i]->issueOrder("bomb", target);
                                                    bomb->play();
                                                }
                                                break;
                                            }

                                            //reinforcement
                                            case 2:{
                                                Card* reinforcement=players[i]->getHand()->firstReinforcement();
                                                if(reinforcement== nullptr){
                                                    cout<<"You do not have any Reinforcement cards!"<<endl;
                                                }else {
                                                    cout << "You got 5 reinforce armies from this card!" << endl;
                                                    players[i]->addArmies(5);
                                                    reinforcement->play();
                                                }
                                                break;
                                            };

                                            //diplomacy
                                            case 3:{
                                                Card* diplomacy=players[i]->getHand()->firstDiplomacy();
                                                if(diplomacy== nullptr){
                                                    cout<<"You do not have any Diplomacy cards!"<<endl;
                                                }else {
                                                    int choice1 = 0;
                                                    while (choice1 < 1 || choice1 > players.size()) {
                                                        cout << "Please choose a player:" << endl;
                                                        for (int j = 1; j <= players.size(); j++) {
                                                            cout << i << ". " << players[j]->getName() << endl;
                                                        }
                                                        cin >> choice1;
                                                    }
                                                    players[i]->issueOrder("diplomacy", players[choice]);
                                                    diplomacy->play();
                                                }
                                                break;
                                            }

                                            //return
                                            case 4:{
                                                cout<<"Got it!"<<endl;
                                                break;
                                            }
                                        }
                                    }
                                }
                                break;
                            }

                            //exit
                            case 3: {
                                cout << "Your round is over." << endl;
                                break;
                            }
                        }
                    }
                }
            }
        break;
    }
}

void GameEngine::executeOrderPhase()
{
    cout<<"-------------------"<<endl;
    cout<<"Executing orders..."<<endl;
    for (int i = 0; i < players.size(); i++){
        for(int j=0; j<players[i]->getOrders().size();j++){
            players[i]->getOrders()[j]->execute();
        }
        players[i]->clearOrders();
    }
    cout<<"Orders executed!"<<endl;
    cout<<"-------------------"<<endl;
}

string GameEngine::getState(){

}

GameEngine::~GameEngine() {

}
