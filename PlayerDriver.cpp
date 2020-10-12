#include "Player.h"

int main() {
    Player* Player1 = new Player("John");
    Player* Player2 = new Player(*Player1, "Jason");
    Player* Player3 = new Player();
    cout << Player1;
    cout << Player2;
    cout << Player3;
    Player1->issueOrder("attack");
    Player2->issueOrder("defend");
    Player3->issueOrder("wait");
    Player1->toAttack();
    Player2->toDefend();
    return 0;
}