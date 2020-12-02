#include "PlayerStrategy.h"

PlayerStrategy::PlayerStrategy() {}
PlayerStrategy::PlayerStrategy(GameEngine *game, Player* player) :game(game), player(player){}
PlayerStrategy::~PlayerStrategy(){}

HumanPlayerStrategy::HumanPlayerStrategy() : PlayerStrategy(){}
HumanPlayerStrategy::HumanPlayerStrategy(GameEngine *game, Player* player): PlayerStrategy(game, player) {}
HumanPlayerStrategy::~HumanPlayerStrategy() {}

void HumanPlayerStrategy::issueOrder() {

}

void HumanPlayerStrategy::toAttack() {

}

void HumanPlayerStrategy::toDefend(int i) {

}

void NeutralPlayerStrategy::issueOrder() {

}

void NeutralPlayerStrategy::toAttack() {

}

void NeutralPlayerStrategy::toDefend(int i) {

}