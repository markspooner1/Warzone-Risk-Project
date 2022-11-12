//
// Created by Brahim Hamid oudjana on 2022-09-17.
//

#include "Player.h"
#include <vector>
#include <string>
#include "Orders.h"

//constructor
Player::Player(OrdersList *orderList, Hand *hand, vector<Territory*> territories) : orderList(orderList), hand(hand),

                                                                                    territories(territories) {}
//Assign all attributes to NULL
Player::Player() {
    this->orderList = NULL;
    this->hand = NULL;
}

//Copy constructor
Player::Player(const Player &player) {
    this->orderList = new OrdersList(*player.orderList);
    this->territories = player.getTerritories();
    this->hand = new Hand(*(player.hand));
}

Player::Player(string name){
    this->name = name;
    this->hand = new Hand();
}
//Destructor
Player::~Player() {
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
vector<Territory*> Player::getTerritories() const {
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
void Player::setTerritories(vector<Territory*> territories) {
    Player::territories = territories;
}

//Player Methods

//method to create an order object and add it to the orderlist (collection of orders)
//the method expects the first param to be an enum issue_order_types to create the correct object
//the other param depend on the type of order issued
void Player::issueOrder(issue_order_types order_type,Deck* a_deck, int i, vector<Territory*> all_territories, int ID, string name, string source, string target = "default", int num_of_units = 0) {

    vector<Territory*> attack_vector = this->toAttack(all_territories);
    target = attack_vector.at(i % attack_vector.size())->getName();

    vector<Territory*> defend_vector = this->toDefend();
    source = defend_vector.at(i % defend_vector.size())->getName();

    switch(order_type)
    {
        case OrderAdvanceType:{
            if(reinforcement_pool == 0){
            OrderAdvance* o = new OrderAdvance(ID,num_of_units, name, source, target);
            this->orderList->addOrder(*o);
            cout<< "\nOrder created and added to the player order list.\n";
            }else{
                cout << "there are still reinforcements !";
                exit(0);
            }
            break;
            }
        case OrderDeployType:{
            
            OrderDeploy* o = new OrderDeploy(ID, num_of_units, name, target);
            this->orderList->addOrder(*o);
            cout<< "\nOrder created and added to the player order list.\n"; 
            
            break;
            }
        case OrderBombType:{
              if(reinforcement_pool == 0){
//            OrderBomb* o = new OrderBomb(ID, name, target);
//            this->orderList->addOrder(*o);
//            cout<< "\nOrder created and added to the player order list.\n";

                  vector<Card*>* cards = (this->getHand())->get_vector_to_cards();
                  bool found = false;

                  for (int i = 0; i < (*cards).size() ; ++i) {
                      if ((*cards).at(i)->get_card_type()->compare("bomb") == 0){
                          found = true;
                          (*cards).at(i)->play(this, a_deck, ID, name, source, target, num_of_units);
                      }
                  }
                  if (found == false){
                      cout << "Order was passed, but player has no corresponding card. No order issued.";
                  }

              } else {
                cout << "there are still reinforcements !";
                exit(0);
            }
            break;
            }
        case OrderBlockadeType:{
             if(reinforcement_pool == 0){
//            OrderBlockade* o = new OrderBlockade(ID, name, target);
//            this->orderList->addOrder(*o);
//            cout<< "\nOrder created and added to the player order list.\n";

                 vector<Card*>* cards = (this->getHand())->get_vector_to_cards();
                 bool found = false;

                 for (int i = 0; i < (*cards).size() ; ++i) {
                     if ((*cards).at(i)->get_card_type()->compare("blockade") == 0){
                         (*cards).at(i)->play(this, a_deck, ID, name, source, target, num_of_units);
                     }
                 }
                 if (found == false){
                     cout << "Order was passed, but player has no corresponding card. No order issued.";
                 }
             } else {
                cout << "there are still reinforcements !";
                exit(0);
            }
            break;
            }
        case OrderAirliftType:{
            
            if(reinforcement_pool == 0){
//            OrderAirlift* o = new OrderAirlift(ID,num_of_units, name, source, target);
//            this->orderList->addOrder(*o);
//            cout<< "\nOrder created and added to the player order list.\n";

                vector<Card*>* cards = (this->getHand())->get_vector_to_cards();
                bool found = false;

                for (int i = 0; i < (*cards).size() ; ++i) {
                    if ((*cards).at(i)->get_card_type()->compare("airlift") == 0){
                        (*cards).at(i)->play(this, a_deck, ID, name, source, target, num_of_units);
                    }
                }
                if (found == false){
                    cout << "Order was passed, but player has no corresponding card. No order issued.";
                }

            } else {
                cout << "there are still reinforcements !";
                exit(0);
            }
            break;
            }
        case OrderNegotiateType:{
            if(reinforcement_pool == 0){
//            OrderNegotiate* o = new OrderNegotiate(ID, name, source, target);
//            this->orderList->addOrder(*o);
//            cout<< "\nOrder created and added to the player order list.\n";

                vector<Card*>* cards = (this->getHand())->get_vector_to_cards();
                bool found = false;

                for (int i = 0; i < (*cards).size() ; ++i) {
                    if ((*cards).at(i)->get_card_type()->compare("diplomacy") == 0){
                        (*cards).at(i)->play(this, a_deck, ID, name, source, target, num_of_units);
                    }
                }
                if (found == false){
                    cout << "Order was passed, but player has no corresponding card. No order issued.";
                }
            }else {
                cout << "there are still reinforcements !";
                exit(0);
            }
            break;
            }
        default:
            cout<< "Order type not recognized. No order was added to the player order list.";
    }

}

//method to defend territories
//return subset of the territories that belong to the player (arbitrary for now)
vector<Territory*> Player::toDefend() {
    vector<Territory*> ToDefendTerritories;

    vector<Territory*> ptr = this->getTerritories();

    int LIMIT = (this->territories).size();
    for (size_t i = 0; i < LIMIT; i++) {
        ToDefendTerritories.push_back(ptr.at(i));
    }
    return ToDefendTerritories;
};


//method to attack territories
//return an arbitary territories that do not belong to the player by creating the attackable territories vector
vector<Territory*> Player::toAttack(const  vector<Territory*> ALLTERRITORIES ) {
    //return arbitrary territories for now

    //vector of territories that do not belong to the player
    vector<Territory*>  attackableTerritories;
    //vector of territories to be returned
    vector<Territory*> ToAttackTerritories;


    //init the attackable vector
    vector<Territory*> ALL = ALLTERRITORIES;
    vector<Territory*> Current = (this->territories);

    int LIMIT1 = Current.size();
    int LIMIT2 = ALL.size();

    for (size_t i = 0; i < LIMIT1; i++) {
        string compared_element = Current.at(i)->getName();

        for (size_t j = 0; j < LIMIT2; j++) {
            if(compared_element == ALL.at(j)->getName()){
                attackableTerritories.push_back(Current.at(i));
                break;
            }

        }
    }


    //assigning arbitrary territories from attackable to toAttack which will be returned
    int LIMIT = (attackableTerritories).size();
    for (size_t i = 0; i < LIMIT; i++) {
        ToAttackTerritories.push_back(attackableTerritories.at(i));
    }
    //delete attackableTerritories;
    return ToAttackTerritories;

}

void Player::addTerritory(Territory *t){
    this->territories.push_back(t);
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
    int LIMIT = (player.getTerritories()).size();
    for (size_t i = 0; i < LIMIT; i++) {
        cout << (player.getTerritories()).at(i)<< endl;
    }

    return out;
}

//Assignment operator = to create a copy of a player
Player &Player::operator=(const Player &player) {

    this->orderList = new OrdersList(*player.orderList);
    this->territories = player.getTerritories();
    this->hand = new Hand(*(player.hand));

    return *this;
}
void Player::setName(string name){
    this->name = name;
}

