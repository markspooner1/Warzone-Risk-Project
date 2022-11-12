//
// Created by Brahim Hamid oudjana on 2022-09-17.
//

#pragma once

#include <vector>
#include "Orders.h"
#include "Map.h"
#include "Cards.h"
using namespace std;
class Territory;
//Attributes:
// Collection of orderList
// collection of territories
// collection of cards

// methods:
// to_defend()
// to_Attack()
//issue_Order()

enum issue_order_types { OrderAdvanceType, OrderDeployType, OrderBombType, OrderBlockadeType, OrderAirliftType, OrderNegotiateType };

class Player {

private:

    OrdersList* orderList;  // collection of Orders
    Hand* hand;            //collection of Cards
    vector<Territory*> territories;     //collection of territories


public:


    Player(Player const &player);   //copy constructor

    Player();   //default Constructor

    Player(OrdersList *orderList, Hand *hand, vector<Territory*> territories);   //constructor

    Player(string name);

    virtual ~Player();      //destructor

    vector<Territory*> toDefend();      //method to defend territories

    vector<Territory*> toAttack(const  vector<Territory*>  ALLTERRITORIES);     //method to attack territories

    //method to create an order object and add it to the orderlist (collection of orders)
    void issueOrder(issue_order_types order_type,Deck* a_deck,int i,vector<Territory*> all_territories, int ID, string name, string source, string target, int num_of_units );

    //Getters:
    OrdersList *getOrders() const;       //getter for the collection orders named orderList

    Hand *getHand() const;      //getter for the collection of cards named hand

    vector<Territory*> getTerritories() const;  //getter for the collection of territories

    //Setters:
    void setOrders(OrdersList *orders);  //setter for the collection orders named orderList

    void setHand(Hand *hand);       //setter for the collection of cards named hand

    void setTerritories(vector<Territory*> territories);        //Setter for the collection of territories

    void addTerritory(Territory *t);

    Player & operator= (const Player&);     //Assignment operator = 

    //Friend method:
    friend ostream & operator << (ostream &out, const Player &player);    // Method to overload the << operator to print the player
    
    string name;

    int *reinforcement_pool;

    void setName(string name);
    
    bool ownsTerritory(Territory *t);
};

void testPlayers();
