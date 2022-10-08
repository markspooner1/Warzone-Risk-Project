#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Orders.h"

void testPlayers() {


/*Invariant:
 * CONST  ALL-TERRITORIES
 * ALL-TERRITORIES = P1 U P2 U ... U Pn U UT(unoccupied Territories)
 *
 * Pn.ATTACKABLE = ALL-TERRITORIES - Pn.TERRITORIES
 * */

/*t0 : ALL-TERRITORIES = UT */

    //Create All territories pointer:
    auto * ALLTERRITORIES = new vector<Territory>;
    ALLTERRITORIES->push_back(Territory("England", "Europe"));
    ALLTERRITORIES->push_back(Territory("Finland", "Europe"));
    ALLTERRITORIES->push_back(Territory("Denmark", "Europe"));
    ALLTERRITORIES->push_back(Territory("Ghana", "Africa"));
    ALLTERRITORIES->push_back(Territory("Egypt", "Africa"));
    ALLTERRITORIES->push_back(Territory("Congo", "Africa"));
    ALLTERRITORIES->push_back(Territory("China", "Asia"));
    ALLTERRITORIES->push_back(Territory("Russia", "Asia"));
    ALLTERRITORIES->push_back(Territory("Singapore", "Asia"));

    //Creating a vector of  Territories to assign to the player
    auto * P1_Territories = new vector<Territory>;
    P1_Territories->push_back(ALLTERRITORIES->at(0));
    P1_Territories->push_back(ALLTERRITORIES->at(1));
    P1_Territories->push_back(ALLTERRITORIES->at(2));


    //Creating a vector of  Territories to assign to the player
    auto * P2_Territories = new vector<Territory>;
    P2_Territories->push_back(ALLTERRITORIES->at(3));
    P2_Territories->push_back(ALLTERRITORIES->at(4));
    P2_Territories->push_back(ALLTERRITORIES->at(5));

    //Creating a vector of  Territories to assign to the player
    auto * P3_Territories = new vector<Territory>;
    P3_Territories->push_back(ALLTERRITORIES->at(6));
    P3_Territories->push_back(ALLTERRITORIES->at(7));
    P3_Territories->push_back(ALLTERRITORIES->at(8));

    //Creating hand pointer to assign to the player
    Hand *hand_p1 = new Hand();
    Hand *hand_p2 = new Hand();
    Hand *hand_p3 = new Hand();

    //Creating OrderList pointer to assign to the player
    auto *order_list_p1 = new OrdersList();
    auto *order_list_p2 = new OrdersList();
    auto *order_list_p3 = new OrdersList();


    //Create players and assign subsets of territories
    auto* p1 = new Player(order_list_p1, hand_p1, P1_Territories);
    cout << "\nplayer 1 (p1) created.\n";
    auto* p2 = new Player(order_list_p2, hand_p2, P2_Territories);
    cout << "\nplayer 2 (p2) created.\n";
    auto* p3 = new Player(order_list_p3, hand_p3, P3_Territories);
    cout << "\nplayer 3 (p3) created.\n";



    //Executing issueOrder() for each player:
    p1->issueOrder(OrderAdvanceType, 1,"p1 order", ALLTERRITORIES->at(1).getName(), ALLTERRITORIES->at(2).getName(), 2);
    p2->issueOrder(OrderAdvanceType, 1,"p2 order", ALLTERRITORIES->at(3).getName(), ALLTERRITORIES->at(2).getName(), 2);
    p3->issueOrder(OrderAdvanceType, 1,"p3 order", ALLTERRITORIES->at(2).getName(), ALLTERRITORIES->at(3).getName(), 2);



    //Executing get territories() for each player and printing the territories stored in the returned vector
    vector<Territory> p1_territories_vector = *(p1->getTerritories());
    cout<< "\nplayer1 (p1) territories:\n";
    int LIMIT = p1_territories_vector.size();
    for (size_t i = 0; i < LIMIT; i++) {
        cout<<p1_territories_vector[i] <<"\n";
    }

    vector<Territory> p2_territories_vector = *(p2->getTerritories());
    cout<< "\nplayer2 (p2) territories:\n";
    LIMIT = p2_territories_vector.size();
    for (size_t i = 0; i < LIMIT; i++) {
        cout<<p2_territories_vector[i]<< "\n";
    }

    vector<Territory> p3_territories_vector = *(p3->getTerritories());
    cout<< "\nplayer3 (p3) territories:\n";
    LIMIT = p3_territories_vector.size();
    for (size_t i = 0; i < LIMIT; i++) {
        cout<<p3_territories_vector[i] << "\n";
    }


    //Executing get hand() for each player and printing it:
    cout<< "\nplayer1 (p1) Hand:\n";
    cout << *(p1->getHand());
    cout<< "\nplayer2 (p2) Hand:\n";
    cout << *(p2->getHand());
    cout<< "\nplayer3 (p3) Hand:\n";
    cout << *(p3->getHand());


    //Executing get order() for each player and printing it:
    cout<< "\nplayer1 (p1) Orders:\n";
    cout << *(p1->getOrders());
    cout<< "\nplayer2 (p2) Orders:\n";
    cout << *(p2->getOrders());
    cout<< "\nplayer3 (p3) Orders:\n";
    cout << *(p3->getOrders())<<"\n";



    //Executing toAttack() for each player and printing the territories stored in the returned vector
    cout<< "\nplayer1 (p1) toAttack:\n";
    vector<Territory> p1_territories_toAttack = *(p1->toAttack(ALLTERRITORIES));

    LIMIT = p1_territories_toAttack.size();
    for (size_t i = 0; i < LIMIT; i++) {
        cout<<p1_territories_toAttack[i]<< "\n";
    }

    cout<< "\nplayer2 (p2) toAttack:\n";
    vector<Territory> p2_territories_toAttack = *(p2->toAttack(ALLTERRITORIES));

    LIMIT = p2_territories_toAttack.size();
    for (size_t i = 0; i < LIMIT; i++) {
        cout<<p2_territories_toAttack[i]<<"\n";
    }

    cout<< "\nplayer3 (p3) toAttack:\n";
    vector<Territory> p3_territories_toAttack = *(p3->toAttack(ALLTERRITORIES));

    LIMIT = p3_territories_toAttack.size();
    for (size_t i = 0; i < LIMIT; i++) {
        cout<<p3_territories_toAttack[i]<<"\n";
    }



    //Executing toDefend() for each player and printing the territories stored in the returned vector
    cout<< "\nplayer1 (p1) toDefend:\n";
    vector<Territory> p1_territories_toDefend = *(p1->toDefend());

    LIMIT = p1_territories_toDefend.size();
    for (size_t i = 0; i < LIMIT; i++) {
        cout<<p1_territories_toDefend[i]<<"\n";
    }

    cout<< "\nplayer2 (p2) toDefend:\n";
    vector<Territory> p2_territories_toDefend = *(p2->toDefend());

    LIMIT = p2_territories_toDefend.size();
    for (size_t i = 0; i < LIMIT; i++) {
        cout<<p2_territories_toDefend[i]<<"\n";
    }

    cout<< "\nplayer3 (p3) toDefend:\n";
    vector<Territory> p3_territories_toDefend = *(p3->toDefend());

    LIMIT = p3_territories_toDefend.size();
    for (size_t i = 0; i < LIMIT; i++) {
        cout<<p3_territories_toDefend[i]<<"\n";
    }


    //overloading the << operator to print the player object:
    cout<< "\nPrinting the player objects:\n";
    cout<< "\nprinting P1\n";
    cout << *p1;
    cout<< "\nprinting P2\n";
    cout << *p2;
    cout<< "\nprinting P3\n";
    cout << *p3;

//Deleting the objects:
delete ALLTERRITORIES;
delete P1_Territories;
delete P2_Territories;
delete P3_Territories;
delete hand_p1;
delete hand_p2;
delete hand_p3;
delete order_list_p1;
delete order_list_p2;
delete order_list_p3;
delete p1;
delete p2;
delete p3;




}

