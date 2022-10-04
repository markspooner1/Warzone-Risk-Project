#include <iostream>
#include "Player.h"
#include "Map.h"

int main() {

/*Invariant:
 * CONST  ALL-TERRITORIES
 * ALL-TERRITORIES = P1 U P2 U ... U Pn U UT(unoccupied Territories)
 *
 * Pn.ATTACHABLE = ALL-TERRITORIES - Pn.TERRITORIES
 * */

/*t0 : ALL-TERRITORIES = UT */

    //Create All territories pointer:
    vector<Territory> * ALLTERRITORIES = new vector<Territory>;
    ALLTERRITORIES->push_back(Territory("England", "Europe"));
    ALLTERRITORIES->push_back(Territory("Finland", "Europe"));
    ALLTERRITORIES->push_back(Territory("Denmark", "Europe"));
    ALLTERRITORIES->push_back(Territory("Ghana", "Africa"));
    ALLTERRITORIES->push_back(Territory("Egypt", "Africa"));
    ALLTERRITORIES->push_back(Territory("Congo", "Africa"));
    ALLTERRITORIES->push_back(Territory("China", "Asia"));
    ALLTERRITORIES->push_back(Territory("Russia", "Asia"));
    ALLTERRITORIES->push_back(Territory("Singapore", "Asia"));

    vector<Territory> * P1_Territories = new vector<Territory>;
    P1_Territories->push_back(ALLTERRITORIES->at(0));
    P1_Territories->push_back(ALLTERRITORIES->at(1));
    P1_Territories->push_back(ALLTERRITORIES->at(2));

    vector<Territory> * P2_Territories = new vector<Territory>;
    P1_Territories->push_back(ALLTERRITORIES->at(3));
    P1_Territories->push_back(ALLTERRITORIES->at(4));
    P1_Territories->push_back(ALLTERRITORIES->at(5));

    vector<Territory> * P3_Territories = new vector<Territory>;
    P1_Territories->push_back(ALLTERRITORIES->at(6));
    P1_Territories->push_back(ALLTERRITORIES->at(7));
    P1_Territories->push_back(ALLTERRITORIES->at(8));

    Hand *hand_p1 = new Hand();
    Hand *hand_p2 = new Hand();
    Hand *hand_p3 = new Hand();



    //Create players and assign subsets of territories
    Player* p1 = new Player(NULL, hand_p1, P1_Territories);
    Player* p2 = new Player(NULL, hand_p2, P2_Territories);
    Player* p3 = new Player(NULL, hand_p3, P3_Territories);
    //issueOrder()

    //get territories

    //get hand
    //getOrders
    //toAttack()
    //toDefend()


