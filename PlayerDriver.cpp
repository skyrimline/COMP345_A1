#include "Player.h"

int main() {
    Player Player1 = new Player("John");
    Player Player2 = new Player(&Player1, "Jason");
    Player player3 = new Player();
    cout << Player1;
    cout << Player2;
    cout << Player3;
    Player1.issueOrder();
    Player2.issueOrder();
    Player3.issueOrder();
    Player1.toAttack();
    Player2.toDefend();
    return 0;
}