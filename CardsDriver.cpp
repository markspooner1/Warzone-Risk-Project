#include "Cards.h"

void testCards() {

	Deck* aDeck = new Deck;

	//initial Deck to assign 30 cards, each type has 5 cards
	aDeck->initial_deck();


	Hand* aHandCard = new Hand;

	//using draw() to random a card from deck, then add it to hand
	cout << "draw 5 cards randomly into hand \n"<<endl;
	for (int i = 0; i < 5; i++) {
		aHandCard->set_cards_in_hand(aDeck->draw());
	}

	//print the current hand
	aHandCard->print_hand_vector();


	//test the play cards order of Hand
	cout<<"\nPlay current hand................................ \n"<<endl;
	int hand_size = aHandCard->get_hand_vector()->size();
	for (int k = 0; k < hand_size; k++) {
		aHandCard->play(aHandCard->get_hand_vector()->at(0), aDeck);
	}

	//delete pointers
	delete aHandCard;
	delete aDeck;
}
