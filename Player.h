//
// Created by Brahim Hamid oudjana on 2022-09-17.
//

#pragma once

#include <vector>
#include "Orders.h"
#include "Map.h"
#include "Cards.h"
using namespace std;

// Collection of orderList
// collection of territoires
// collection of cards
// methods:
// to_defend()
// to_Attack()
//issue_Order()

class Player {

private:


    OrderList* orderList;
    Hand* hand;
    vector<Territory> *territories;
    // territories1->at[index]

public:


    Player(Player const *player);

    Player(OrderList *orderList, Hand *hand, vector<Territory> *territories);

    virtual ~Player();

    vector<Territory>* toDefend();

    vector<Territory>* toAttack(const  vector<Territory> * ALLTERRITORIES);

    void  issueOrder();

    OrderList *getOrders() const;

    Hand *getHand() const;

    vector<Territory> *getTerritories() const;

    void setOrders(OrderList *orders);

    void setHand(Hand *hand);

    void setTerritories(vector<Territory> *territories);

    friend ostream & operator << (ostream &out, const Player *player);

};


