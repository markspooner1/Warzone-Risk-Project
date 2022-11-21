//
// Created by Brahim Hamid oudjana on 2022-09-17.
//

#include "Player.h"
#include <vector>
#include <string>
#include "Orders.h"
#include <random>
//constructor
Player::Player(OrdersList *orderList, Hand *hand, vector<Territory*> territories) : orderList(orderList), hand(hand),

                                                                                    territories(territories) {}
//Assign all attributes to NULL
Player::Player() {
    //this->orderList = NULL;
    this->hand = NULL;
}

//Copy constructor
Player::Player(const Player &player) {
   //this->orderList = new OrdersList(*player.orderList);
    this->territories = player.getTerritories();
    this->hand = new Hand(*(player.hand));
}

Player::Player(string name){
    this->orderList = new OrdersList();
    this->name = name;
    this->hand = new Hand();
    this->reinforcement_pool = 0;
}
//Destructor
Player::~Player() {
    this->hand = NULL;
   // this->orderList = NULL;
};


//Getters:

//getter for the collection orders named orderList
OrdersList* Player::getOrders() const {
    return orderList;
}

//getter for the collection of cards named hand
Hand *Player::getHand() const {
    return hand;
}

//getter for the collection of territories
vector<Territory*> Player::getTerritories() const {
    return territories;
}


//Setters:

//setter for the collection orders named orderList
void Player::setOrders(OrdersList orders) {
    orderList = &orders;
}

//setter for the collection of cards named hand
void Player::setHand(Hand *hand) {
    Player::hand = hand;
}

//Setter for the collection of territories
void Player::setTerritories(vector<Territory*> territories) {
    Player::territories = territories;
}

//Player Methods

void Player::issueOrder(Deck *d) {
    this->ps->issueOrder(d);
}

//method to defend territories
//return subset of the territories that belong to the player (arbitrary for now)
vector<Territory*> Player::toDefend() {
    return this->ps->toDefend();
}


//method to attack territories
//return an arbitary territories that do not belong to the player by creating the attackable territories vector
vector<Territory*> Player::toAttack() {
    return this->ps->toAttack();
}

void Player::addTerritory(Territory *t){
    this->territories.push_back(t);
    t->owner = this;
}
// Method to overload the << operator to print the player
//returns the attributes of the player, namely hand, orders, and territories.
ostream & operator << (ostream &out, const Player &player)
{
    cout<< "\nplayer Hand:\n";
    cout << *(player.getHand());

    cout<< "\nplayer Orders:\n";
    cout << (player.getOrders());


    cout<< "\nplayer territories:\n";
    int LIMIT = (player.getTerritories()).size();
    for (size_t i = 0; i < LIMIT; i++) {
        cout << (player.getTerritories()).at(i)<< endl;
    }

    return out;
}

//Assignment operator = to create a copy of a player
Player &Player::operator=(const Player &player) {

    this->orderList = player.orderList;
    this->territories = player.getTerritories();
    this->hand = new Hand(*(player.hand));

    return *this;
}
void Player::setName(string name){
    this->name = name;
}


bool Player::ownsTerritory(string t){
    for(int i = 0; i < this->getTerritories().size(); i++){
        try {//cout << this->getTerritories()[i]->getName();
            if(this->getTerritories()[i]->getName().compare(t) == 0){
            return true;
        }
        } catch(std::exception& e){ return true;}
        
    }
    return false;
}

Territory* Player::getTerritoryFromName(string t){
   for(int i = 0; i < this->getTerritories().size(); i++){
       if(this->getTerritories()[i]->getName() == t){
           return this->getTerritories()[i];
       }
   }

}
void Player::removeTerritory(Territory *t){
    this->territories.erase(std::remove(this->territories.begin(),this->territories.end(),t),this->territories.end());

}

