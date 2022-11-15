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

//method to create an order object and add it to the orderlist (collection of orders)
//the method expects the first param to be an enum issue_order_types to create the correct object
//the other param depend on the type of order issued
void Player::issueOrder(Deck *d) {
      std::random_device dev;
      std::mt19937 rng(dev());
     vector<Territory*> attack_vector = this->toAttack();
    // target = attack_vector.at(i % attack_vector.size())->getName();
     vector<Territory*> defend_vector = this->toDefend();
    if(this->reinforcement_pool > 0){
        cout << "\n\t---DEPLOY ORDERS----\n" <<endl;
        std::uniform_int_distribution<std::mt19937::result_type> dist1(1 ,this->reinforcement_pool);
        int deploynum = dist1(rng);
        std::uniform_int_distribution<std::mt19937::result_type> dist2(0 ,this->getTerritories().size() - 1);
        int terr = dist2(rng);
    
        Territory* territorytodeploy = this->getTerritories()[terr];
        cout << "Player: " << this->name << " has " << this->reinforcement_pool << " armies left in its reinforcement pool" << endl;
        cout << "Player: " << this->name << " has chosen to deploy " << deploynum << " armies to: " << territorytodeploy->getName() << endl;
        cout << "\n";
        this->orderList->addOrder((new OrderDeploy(this, 0, deploynum, "deploy",territorytodeploy)));
        this->reinforcement_pool -= deploynum;
        }
    else{
        

        int rands = rand() % 5 + 1;
        if((this->getHand()->get_hand_vector()->size() == 0) || rands < 3){
            cout << "\n\t---Advance ORDERS----\n" <<endl;
            string attackOrDefend = "";
            int x = rand() % 2 + 1;
            if(x == 1){ 
                attackOrDefend = "Attack";
            }
            else{ 
                attackOrDefend = "Defend";

            }
            if(attackOrDefend.compare("Attack") == 0){

                    std::uniform_int_distribution<std::mt19937::result_type> dist3(0 ,defend_vector.size() - 1);

                    int terr = dist3(rng);

                    Territory* source = defend_vector[terr];
                    std::uniform_int_distribution<std::mt19937::result_type> dist4(1 , 5);
                    int units = dist4(rng);
                    std::uniform_int_distribution<std::mt19937::result_type> dist5(0 , attack_vector.size() - 1);
                    terr = dist5(rng);
                    Territory* target = attack_vector[terr];
                    cout << "Player: " << this->name << " has chosen to Advance(attack) "  << target->getName() <<" with " << units << " armies" <<endl;
                      cout << "\n";
                    this->orderList->addOrder((new OrderAdvance(this,0,units, "Advance", source, target)));
                }
            else{
                std::uniform_int_distribution<std::mt19937::result_type> dist7(0 , defend_vector.size() - 1);
                int terr = dist7(rng);
                Territory* source = defend_vector[terr];
                std::uniform_int_distribution<std::mt19937::result_type> dist8(1 , 6);
                int units = dist8(rng);
                std::uniform_int_distribution<std::mt19937::result_type> dist9(0 , defend_vector.size() - 1);
                terr = dist9(rng);
                Territory* source2 = defend_vector[terr];
                cout << "Player: " << this->name << " has chosen to Advance(defend) " << source2->getName() <<" with "<< units << " armies" << endl;
                  cout << "\n";
                this->orderList->addOrder((new OrderAdvance(this,0, units, "Defend", source, source2))); 
            }
        }
        else{
            if(this->getHand()->get_hand_vector()->size() != 0){
                cout << "\n\t---CARD PLAYING----\n" << endl;
                
                Card*c = (this->getHand()->get_hand_vector()->at(0));
                cout << "good" << endl;
                if(*c->get_card_type() == "airlift"){
                                                            

                    cout << "Player " << this->name << " is playing " << *c->get_card_type() << endl;
                    cout << "Airlift Order Issued" << endl;
                    std::uniform_int_distribution<std::mt19937::result_type> dist10(0 , defend_vector.size() - 1);
                    int terr = dist10(rng);
                    Territory* source = defend_vector[terr];
                    std::uniform_int_distribution<std::mt19937::result_type> dist11(1 , 6);
                    int units = dist11(rng);
                    terr = rand() % attack_vector.size();
                    std::uniform_int_distribution<std::mt19937::result_type> dist12(0 , attack_vector.size() - 1);
                    terr = dist12(rng);
                    Territory* target = attack_vector[terr];
                    c->play(this, d, 0, "Airlift", source, target, units);
                    // this->orderList->addOrder((new OrderAirlift(this,0, units, "Airlift", source, target)));
                    // this->getHand()->remove_card_played_from_hand_vector(c);
                }
                else if(*c->get_card_type() == "bomb"){

                    cout << "Player " << this->name << " is playing " << *c->get_card_type() << endl;
                    std::uniform_int_distribution<std::mt19937::result_type> dist13(0 , attack_vector.size() - 1);
                    int terr = dist13(rng);
                    Territory* target = attack_vector[terr];
                    cout << target << endl;
                    c->play(this, d, 0, "Bomb",target, target, 0);
                    // this->orderList->addOrder((new OrderBomb(this,0,"Bomb", target)));
                    // this->getHand()->remove_card_played_from_hand_vector(c);

                }
                else if(*c->get_card_type() == "blockade"){

                    cout << "Player " << this->name << " is playing " << *c->get_card_type() << endl;
                    cout << "Blockade Order Issued" << endl;
                    std::uniform_int_distribution<std::mt19937::result_type> dist14(0 , defend_vector.size() - 1);
                    int terr = dist14(rng);
                    Territory* source = defend_vector[terr];
                    c->play(this, d, 0, "Blockade",source, source, 0);
                    // this->orderList->addOrder((new OrderBlockade(this,0, "Blockade", source)));
                    // this->getHand()->remove_card_played_from_hand_vector(c);

                }else if(*c->get_card_type() == "diplomacy"){

                    cout << "Player " << this->name << " is playing " << *c->get_card_type() << endl;
                    cout << "Diplomacy Order Issued" << endl;
                    std::uniform_int_distribution<std::mt19937::result_type> dist15(0 , defend_vector.size() - 1);
                    int terr = dist15(rng);
                    Territory* source = defend_vector[terr];
                    std::uniform_int_distribution<std::mt19937::result_type> dist16(1 , 6);
                    int units = dist16(rng);
                    terr = rand() % attack_vector.size();
                    std::uniform_int_distribution<std::mt19937::result_type> dist17(0 , attack_vector.size() - 1);
                    terr = dist17(rng);
                    Territory* target = attack_vector[terr];
                    c->play(this, d, 0, "Negotiate", source, target, 0);
                    // this->orderList->addOrder((new OrderNegotiate(this,0, "Negotiate", source, target)));
                    // this->getHand()->remove_card_played_from_hand_vector(c);
                }
                else if(*c->get_card_type() == "reinforcement"){
                    this->reinforcement_pool += 5;
                    std::uniform_int_distribution<std::mt19937::result_type> dist20(0 ,this->getTerritories().size() - 1);
                    int terr = dist20(rng);
                    Territory* territorytodeploy = this->getTerritories()[terr];
                    this->orderList->addOrder((new OrderDeploy(this, 0, 5, "deploy",territorytodeploy)));
                    cout << "Player " << this->name << " has used their reinforcement card";
                    this->getHand()->remove_card_played_from_hand_vector(c);
                }

            }
        }
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
}


//method to attack territories
//return an arbitary territories that do not belong to the player by creating the attackable territories vector
vector<Territory*> Player::toAttack() {
    vector<Territory*>  attackableTerritories;
    for(int i = 0; i < this->getTerritories().size(); i++){
        for(int j = 0; j < this->getTerritories()[i]->getNeighbours().size(); j++){
                attackableTerritories.push_back(this->getTerritories()[i]->getNeighbours()[j]);
        }
    }
    return attackableTerritories;
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
    cout << t->getName() << " removed from players territories " << this->name << "'s list of territories" << endl;
    this->territories.erase(std::remove(this->territories.begin(),this->territories.end(),t),this->territories.end());

}

