//
// Created by Brahim Hamid oudjana on 2022-09-17.
//

#pragma once

#include <vector>
#include "Order.h"
#include "Map.h"
#include "Card.h"
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
    //vector<Order *> Orders;
    //vector<Card *> Cards;

    OrderList* orderList;
    Hand* hand;
    vector<Territory *> territories;


public:

    Player(OrderList orderList, Hand hand, vector<Territory *> territories);

    Player(Player const &player);

    virtual ~Player();

    vector<Territory *> toDefend();

    vector<Territory *> toAttack();

    void  issueOrder();

    OrderList *getOrders() const;

    Hand *getHand() const;

    const vector<Territory *> &getTerritories() const;

    void setOrders(OrderList *orders);

    void setHand(Hand *hand);

    void setTerritories(const vector<Territory *> &territories);


};


