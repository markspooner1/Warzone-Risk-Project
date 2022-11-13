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
    CommandProcessing *c = new CommandProcessing();
    GameEngine *g = new GameEngine();
    g->startupPhase(c);
    g->mainGameLoop();



}


