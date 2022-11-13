//
// Created by Brahim Hamid oudjana on 2022-11-10.
//
#include "Orders.h"
#include "Map.h"
#include "Cards.h"
#include "Player.h"
#include <vector>
#include "GameEngine.h"

// class order_adt{
// public:
//     order_adt(vector<issue_order_types> OrderType,
//     vector<int> ID,
//     vector<string> name,
//     vector<string> source,
//     vector<string> target,
//     vector<int> number_of_units){
//         this->OrderType = OrderType;
//                 this->ID=ID;
//         this->name=name
//         this->source=source
//         this->target = target
//         this->number_of_units = number_of_units;
//     };
//
//
//     vector<issue_order_types> OrderType;
//     vector<int> ID;
//     vector<string> name;
//     vector<string> source;
//     vector<string> target;
//     vector<int> number_of_units;
//
// };

int main()
{
    //    p1->issueOrder(OrderAdvanceType, 1,"p1 order", ALLTERRITORIES->at(1).getName(), ALLTERRITORIES->at(2).getName(), 2);
    //    p2->issueOrder(OrderAdvanceType, 1,"p2 order", ALLTERRITORIES->at(3).getName(), ALLTERRITORIES->at(2).getName(), 2);
    //    p3->issueOrder(OrderAdvanceType, 1,"p3 order", ALLTERRITORIES->at(2).getName(), ALLTERRITORIES->at(3).getName(), 2);
    //
    //    OrderAdvanceType, 1,"p1 order", ALLTERRITORIES->at(1).getName(), ALLTERRITORIES->at(2).getName(), 2

    CommandProcessing *c = new CommandProcessing();
    GameEngine *g = new GameEngine();
    g->startupPhase(c);

    cout << "test game";
    vector<vector<string>> Orders;

    for (Player *p : g->players)
    {
        cout << *(p->reinforcement_pool) << "\n";
    }

    for (int i = 0; i < g->players.size(); i++)
    {
        Player *p = g->players.at(i);
        cout << "\nPlayer " << p->name << "drew cards: " << endl;
        // for (Card *c : *p->getHand()->get_hand_vector())

        // for (int j = 0; j < p->getHand()->get_hand_vector()->size(); j++)
        // {
        //     if (p->getHand()->get_hand_vector()->at(j)->get_card_type()->compare("bomb") == 0)
        //     {
        //         Orders.at(i).at(j) = "OrderBombType, ID, num_of_units, name,,target";
        //     }
        //     else if (p->getHand()->get_hand_vector()->at(j)->get_card_type()->compare("blockade") == 0)
        //     {
        //         Orders.at(i).at(j) = "OrderBlockadeType, ID, num_of_units, name,,target";
        //     }
        //     else if (p->getHand()->get_hand_vector()->at(j)->get_card_type()->compare("airlift") == 0)
        //     {
        //         Orders.at(i).at(j) = "OrderAirliftType, ID, num_of_units, name,,target";
        //     }
        //     else if (p->getHand()->get_hand_vector()->at(j)->get_card_type()->compare("diplomacy") == 0)
        //     {
        //         Orders.at(i).at(j) = "OrderNegotiateType, ID, num_of_units, name,,target";
        //     }
        // }

        // for(int i =0;i < p->getHand()->get_vector_to_cards()->size();i++){
        //     cout << p->getHand()->get_vector_to_cards()->at(i)->get_card_type();
        //     cout << "somme bullshiiit";
        // }
        // cout << "\n";
        // for(int i=0;(*(p->getHand())).size();i++)
    }
    // vector<vector<string>> Orders;
    // Orders.at(0).at(0) = "OrderDeployType, ID, num_of_units, name,,target";
    // Orders.at(0).at(1) = "OrderDeployType,ID, num_of_units, name,,target";
    // Orders.at(0).at(2) = "OrderAdvanceType, ID,num_of_units, name, source, target";
    // Orders.at(0).at(3) = "OrderAdvanceType, ID,num_of_units, name, source, target";
    // Orders.at(0).at(4) = "OrderAirliftType, ID,num_of_units, name, source, target";

    // Orders.at(1).at(0) = "OrderDeployType, ID, num_of_units, name,,target";
    // Orders.at(1).at(1) = "OrderDeployType,ID, num_of_units, name,,target";
    // Orders.at(1).at(2) = "OrderAdvanceType, ID,num_of_units, name, source, target";
    // Orders.at(1).at(3) = "OrderAdvanceType, ID,num_of_units, name, source, target";
    // Orders.at(1).at(4) = "OrderAirliftType, ID,num_of_units, name, source, target";

    // Orders.at(2).at(0) = "OrderDeployType, ID, num_of_units, name,,target";
    // Orders.at(2).at(1) = "OrderDeployType, ID, num_of_units, name,,target";
    // Orders.at(2).at(2) = "OrderAdvanceType, ID,num_of_units, name, source, target";
    // Orders.at(2).at(3) = "OrderAdvanceType, ID,num_of_units, name, source, target";
    // Orders.at(2).at(4) = "OrderAirliftType, ID,num_of_units, name, source, target";

    // g->mainGameLoop(Orders);
}
