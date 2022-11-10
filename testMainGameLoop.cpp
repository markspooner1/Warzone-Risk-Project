//
// Created by Brahim Hamid oudjana on 2022-11-10.
//
#include "Orders.h"
#include "Map.h"
#include "Cards.h"
#include "Player.h"
#include <vector>
#include "GameEngine.h"



//class order_adt{
//public:
//    order_adt(vector<issue_order_types> OrderType,
//    vector<int> ID,
//    vector<string> name,
//    vector<string> source,
//    vector<string> target,
//    vector<int> number_of_units){
//        this->OrderType = OrderType;
//                this->ID=ID;
//        this->name=name
//        this->source=source
//        this->target = target
//        this->number_of_units = number_of_units;
//    };
//
//
//    vector<issue_order_types> OrderType;
//    vector<int> ID;
//    vector<string> name;
//    vector<string> source;
//    vector<string> target;
//    vector<int> number_of_units;
//
//};

void testMainGameLoop(){
//    p1->issueOrder(OrderAdvanceType, 1,"p1 order", ALLTERRITORIES->at(1).getName(), ALLTERRITORIES->at(2).getName(), 2);
//    p2->issueOrder(OrderAdvanceType, 1,"p2 order", ALLTERRITORIES->at(3).getName(), ALLTERRITORIES->at(2).getName(), 2);
//    p3->issueOrder(OrderAdvanceType, 1,"p3 order", ALLTERRITORIES->at(2).getName(), ALLTERRITORIES->at(3).getName(), 2);
//
//    OrderAdvanceType, 1,"p1 order", ALLTERRITORIES->at(1).getName(), ALLTERRITORIES->at(2).getName(), 2

    GameEngine e;
    e.players;
    e.map;

    vector<vector<string>> Orders;

    Orders.at(0).at(0) = "OrderDeployType, ID, num_of_units, name,,target";
    Orders.at(0).at(1) = "OrderDeployType,ID, num_of_units, name,,target";
    Orders.at(0).at(2) = "OrderAdvanceType, ID,num_of_units, name, source, target";
    Orders.at(0).at(3) = "OrderAdvanceType, ID,num_of_units, name, source, target";
    Orders.at(0).at(4) = "OrderAirliftType, ID,num_of_units, name, source, target";

    Orders.at(1).at(0) = "OrderDeployType, ID, num_of_units, name,,target";
    Orders.at(1).at(1) = "OrderDeployType,ID, num_of_units, name,,target";
    Orders.at(1).at(2) = "OrderAdvanceType, ID,num_of_units, name, source, target";
    Orders.at(1).at(3) = "OrderAdvanceType, ID,num_of_units, name, source, target";
    Orders.at(1).at(4) = "OrderAirliftType, ID,num_of_units, name, source, target";

    Orders.at(2).at(0) = "OrderDeployType, ID, num_of_units, name,,target";
    Orders.at(2).at(1) = "OrderDeployType, ID, num_of_units, name,,target";
    Orders.at(2).at(2) = "OrderAdvanceType, ID,num_of_units, name, source, target";
    Orders.at(2).at(3) = "OrderAdvanceType, ID,num_of_units, name, source, target";
    Orders.at(2).at(4) = "OrderAirliftType, ID,num_of_units, name, source, target";

    e.mainGameLoop(Orders);






}


