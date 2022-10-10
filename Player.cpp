//
// Created by Brahim Hamid oudjana on 2022-09-17.
//

#include "Player.h"
#include <vector>
#include <string>
#include "Orders.h"

//constructor
Player::Player(OrdersList *orderList, Hand *hand, vector<Territory> *territories) : orderList(orderList), hand(hand),

                                                                                    territories(territories) {}
//Assign all attributes to NULL
Player::Player() {
    this->orderList = NULL;
    this->territories = NULL;
    this->hand = NULL;
}

//Copy constructor
Player::Player(const Player &player) {
    this->orderList = new OrdersList(*player.orderList);
    this->territories = new vector<Territory>(*(player.territories));
    this->hand = new Hand(*(player.hand));
}

//Destructor
Player::~Player() {
    this->territories = NULL;
    this->hand = NULL;
    this->orderList = NULL;
};


//Getters:

//getter for the collection orders named orderList
OrdersList *Player::getOrders() const {
    return orderList;
}

//getter for the collection of cards named hand
Hand *Player::getHand() const {
    return hand;
}

//getter for the collection of territories
vector<Territory>* Player::getTerritories() const {
    return territories;
}


//Setters:

//setter for the collection orders named orderList
void Player::setOrders(OrdersList *orders) {
    Player::orderList = orders;
}

//setter for the collection of cards named hand
void Player::setHand(Hand *hand) {
    Player::hand = hand;
}

//Setter for the collection of territories
void Player::setTerritories(vector<Territory> *territories) {
    Player::territories = territories;
}

//Player Methods

//method to create an order object and add it to the orderlist (collection of orders)
//the method expects the first param to be an enum issue_order_types to create the correct object
//the other param depend on the type of order issued
void Player::issueOrder(issue_order_types order_type, int ID, string name, string source, string target = "default", int num_of_units = 0) {

    switch(order_type)
    {
        case OrderAdvanceType:{
            OrderAdvance* o = new OrderAdvance(ID,num_of_units, name, source, target);
            this->orderList->addOrder(*o);
            cout<< "\nOrder created and added to the player order list.\n";
            break;}
        case OrderDeployType:{
            OrderDeploy* o = new OrderDeploy(ID, num_of_units, name, target);
            this->orderList->addOrder(*o);
            cout<< "\nOrder created and added to the player order list.\n";
            break;}
        case OrderBombType:{
            OrderBomb* o = new OrderBomb(ID, name, target);
            this->orderList->addOrder(*o);
            cout<< "\nOrder created and added to the player order list.\n";
            break;}
        case OrderBlockadeType:{
            OrderBlockade* o = new OrderBlockade(ID, name, target);
            this->orderList->addOrder(*o);
            cout<< "\nOrder created and added to the player order list.\n";
            break;}
        case OrderAirliftType:{
            OrderAirlift* o = new OrderAirlift(ID,num_of_units, name, source, target);
            this->orderList->addOrder(*o);
            cout<< "\nOrder created and added to the player order list.\n";
            break;}
        case OrderNegotiateType:{
            OrderNegotiate* o = new OrderNegotiate(ID, name, source, target);
            this->orderList->addOrder(*o);
            cout<< "\nOrder created and added to the player order list.\n";
            break;}
        default:
            cout<< "Order type not recognized. No order was added to the player order list.";
    }

}

//method to defend territories
//return subset of the territories that belong to the player (arbitrary for now)
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


//method to attack territories
//return an arbitary territories that do not belong to the player by creating the attackable territories vector
vector<Territory>* Player::toAttack(const  vector<Territory> * ALLTERRITORIES ) {
    //return arbitrary territories for now

    //vector of territories that do not belong to the player
    vector<Territory> * attackableTerritories = new vector<Territory>;
    //vector of territories to be returned
    vector<Territory> * ToAttackTerritories = new vector<Territory>;


    //init the attackable vector
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


    //assigning arbitrary territories from attackable to toAttack which will be returned
    int LIMIT = (attackableTerritories)->size();
    for (size_t i = 0; i < LIMIT; i++) {
        ToAttackTerritories->push_back(attackableTerritories->at(i));
        i++;
    }
    delete attackableTerritories;
    return ToAttackTerritories;

}


// Method to overload the << operator to print the player
//returns the attributes of the player, namely hand, orders, and territories.
ostream & operator << (ostream &out, const Player &player)
{
    cout<< "\nplayer Hand:\n";
    cout << *(player.getHand());

    cout<< "\nplayer Orders:\n";
    cout << *(player.getOrders());


    cout<< "\nplayer territories:\n";
    int LIMIT = (player.getTerritories())->size();
    for (size_t i = 0; i < LIMIT; i++) {
        cout << (player.getTerritories())->at(i)<< endl;
    }

    return out;
}

//Assignment operator = to create a copy of a player
Player &Player::operator=(const Player &player) {

    this->orderList = new OrdersList(*player.orderList);
    this->territories = new vector<Territory>(*(player.territories));
    this->hand = new Hand(*(player.hand));

    return *this;
}

