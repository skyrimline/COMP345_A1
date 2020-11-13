#ifndef GAMEENGINE_H
#define GAMEENGINE_H

class Map;
class Player;
class Card;
class Hand;

class GameEngine
{
public:
    GameEngine();

private:
    Map *gameMap;
    Player *players[];
    Hand *cards;
};

#endif // GAMEENGINE_H