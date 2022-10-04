//
// Created by Brahim Hamid oudjana on 2022-09-17.
//

#include "Player.h"
#include <vector>
#include <string>


Player::Player(OrderList *orderList, Hand *hand, vector<Territory> *territories) : orderList(orderList), hand(hand),
                                                                                    territories(territories) {}

//Copy constructor
Player::Player(const Player *player) {
    this->orderList = player->getOrders();
    this->territories = player->getTerritories();
    this->hand = player->getHand();
}

//Destructor
Player::~Player() {
    this->territories = NULL;
    this->hand = NULL;
    this->orderList = NULL;
};


//Getters:
OrderList *Player::getOrders() const {
    return orderList;
}

Hand *Player::getHand() const {
    return hand;
}

vector<Territory>* Player::getTerritories() const {
    return territories;
}


//Setters:
void Player::setOrders(OrderList *orders) {
    Player::orderList = orders;
}

void Player::setHand(Hand *hand) {
    Player::hand = hand;
}

void Player::setTerritories(vector<Territory> *territories) {
    Player::territories = territories;
}

//Player Methods
void Player::issueOrder() {
    // Add order params
    //construct an Order object
    //append the object to the ordersList
    Order* order = new Order();
    this->orderList.Append(order); // Add method non-static in Orderlist
}

vector<Territory>* Player::toDefend() {
    vector<Territory>* ToDefendTerritories = new vector<Territory>;

    vector<Territory>* ptr = this->getTerritories();

    int LIMIT = (this->territories)->size();
    for (size_t i = 0; i < LIMIT; i++) {
        ToDefendTerritories->push_back(ptr->at(i));
        i++;
    }
    return ToDefendTerritories;
};

vector<Territory>* Player::toAttack(const  vector<Territory> * ALLTERRITORIES ) {
    //return arbitrary territories for now
    //Must access Territories not in the possession of the current player
    vector<Territory> * attackableTerritories = new vector<Territory>;

    vector<Territory> * ToAttackTerritories = new vector<Territory>;

    vector<Territory> ALL = *ALLTERRITORIES;
    vector<Territory> Current = *(this->territories);

    int LIMIT1 = Current.size();
    int LIMIT2 = ALL.size();

    for (size_t i = 0; i < LIMIT1; i++) {
        string compared_element = Current.at(i).getName();

        for (size_t j = 0; j < LIMIT2; j++) {
            if(compared_element == ALL.at(j).getName()){
                attackableTerritories->push_back(Current.at(i));
                break;
            }

        }
    }

    int LIMIT = (attackableTerritories)->size();
    for (size_t i = 0; i < LIMIT; i++) {
        ToAttackTerritories->push_back(attackableTerritories->at(i));
        i++;
    }
    return ToAttackTerritories;

}


ostream & operator << (ostream &out, const Player *player)
{
    out <<"Hand:\t" <<player->getHand() << "\n"; //Fix this
    out <<"orderList:\t" <<*(player->getOrders()) << "\n";//Fix this
    out <<"territories:\n";

    int LIMIT = (player->getTerritories())->size();
    for (size_t i = 0; i < LIMIT; i++) {
        cout << (player->getTerritories())->at(i)<< endl;
    }

    return out;
}

/*
//
// Created by Brahim Hamid oudjana on 2022-09-17.
//

#include "Player.h"
#include <vector>

Player::Player(OrderList *orderList, Hand *hand, vector<Territory> *territories) {
    this->orderList = orderList;
    this->territories2 = territories;
    this->hand = hand;
}

//Copy constructor
Player::Player(const Player *player) {
    this->orderList = player->getOrders();
    this->territories2 = player->getTerritories();
    this->hand = player->getHand();
}

//Destructor
Player::~Player() {
    this->territories2 = NULL;
    this->orderList = NULL;
    this->hand = NULL;
};


//Getters:
OrderList *Player::getOrders() const {
    return orderList;
}

Hand *Player::getHand() const {
    return hand;
}
/*
const vector<Territory *> Player::getTerritories() const {
    return territories;
}*/
/*
const vector<Territory>* Player::getTerritories() const {
    return territories2;
}

//Setters:
void Player::setOrders(OrderList *orders) {
    Player::orderList = orders;
}

void Player::setHand(Hand *hand) {
    Player::hand = hand;
}

/*void Player::setTerritories(const vector<Territory *> &territories) {
    territories = territories;
}*/
/*
void Player::setTerritories( vector<Territory>* territories) {
    territories2 = territories;
}

void Player::issueOrder() {
    // Add order params
    //construct an Order object
    //append the object to the ordersList
    Order* order = new Order();
    this->orderList.Append(order);
}
vector<Territory >* Player::toDefend() {
    vector<Territory*> ToDefendTerritories;
    int LIMIT = (this->territories2).size();
    for (size_t i = 0; i < LIMIT; i++) {
        ToDefendTerritories.push_back(this->territories2[i]);
        i++;
    }
    return ToDefendTerritories;
};

vector<Territory *> Player::toAttack() {
    //return arbitrary territories for now
    //Must access Territories not in the possession of the player
}*/










