#include "PlayerStrategy.h"

PlayerStrategy::PlayerStrategy(Player *p){
    this->player = p;
}
HumanPlayerStrategy::HumanPlayerStrategy(Player *p) : PlayerStrategy(p){

}
AggressivePlayerStrategy::AggressivePlayerStrategy(Player *p) : PlayerStrategy(p){

}
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player *p) : PlayerStrategy(p){

}
NeutralPlayerStrategy::NeutralPlayerStrategy(Player *p) : PlayerStrategy(p){

}
CheaterPlayerStrategy::CheaterPlayerStrategy(Player *p) : PlayerStrategy(p){

}