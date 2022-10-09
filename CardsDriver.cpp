#include "Cards.h"
#include "Player.h"
#include "Orders.h"
#include "Map.h"

void testCards() {

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


    //Creating OrderList pointer to assign to the player
    auto *Orderlist_p1 = new OrdersList();



	Deck* aDeck = new Deck;

	//initial Deck to assign 30 cards, each type has 5 cards
	aDeck->initial_deck();


	Hand* aHandCard = new Hand;

    //Create players and assign subsets of territories
    auto* p1 = new Player(Orderlist_p1, aHandCard, P1_Territories);

	//using draw() to random a card from deck, then add it to hand
	cout << "draw 5 cards randomly into hand \n"<<endl;
	for (int i = 0; i < 5; i++) {
		aHandCard->set_cards_in_hand(aDeck->draw());
	}

	//print the current hand
	aHandCard->print_hand_vector();


	//test the play method of Card
	int hand_size = aHandCard->get_hand_vector()->size();
	for (int k = 0; k < hand_size; k++) {
		Card* card =  aHandCard->get_hand_vector()->at(k);
		card->play(p1,aDeck);
	}

	//delete pointers
	delete aHandCard;
	delete aDeck;
}

