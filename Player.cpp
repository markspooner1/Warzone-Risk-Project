//
// Created by Brahim Hamid oudjana on 2022-09-17.
//

#include "Player.h"

Player::Player(OrderList orderList, Hand hand, vector<Territory *> territories) {
    this->orderList = orderList;
    this->territories = territories;
    this->hand = hand;
}

//Copy constructor
Player::Player(const Player &player) {
    this->orderList = player.getOrders();
    this->territories = player.getTerritories();
    this->hand = player.getHand();
}

//Destructor
Player::~Player() {
    delete this;
};


//Getters:
OrderList *Player::getOrders() const {
    return orderList;
}

Hand *Player::getHand() const {
    return hand;
}

const vector<Territory *> &Player::getTerritories() const {
    return territories;
}

//Setters:
void Player::setOrders(OrderList *orders) {
    Player::orderList = orders;
}

void Player::setHand(Hand *hand) {
    Player::hand = hand;
}

void Player::setTerritories(const vector<Territory *> &territories) {
    territories = territories;
}

void Player::issueOrder() {
    // Add order params
    //construct an Order object
    //append the object to the ordersList
    Order* order = new Order();
    this->orderList.Append(order);
}
vector<Territory *> Player::toDefend() {
    vector<Territory *> ToDefendTerritories;
    int LIMIT = (this->territories).size();
    for (size_t i = 0; i < LIMIT; i++) {
        ToDefendTerritories.push_back(this->territories[i]);
        i++;
    }
};
vector<Territory *> Player::toAttack() {
    //return arbitrary territories for now
    //Must access Territories not in the possession of the player
}



