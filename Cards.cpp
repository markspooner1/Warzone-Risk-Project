#include "Cards.h"
#include "Player.h"
#include "Map.h"

Card::Card()
{
}

//Destructor
Card::~Card()
{
}


//Card copy constructor
Card::Card(const Card & c)
{
	this->card_types = *new vector<string>(c.card_types);
	this->card_type = new string(*(c.card_type));
}

Card & Card::operator=(const Card & c)
{
    this->card_type = new string(*(c.card_type));
	this->card_types = *new vector<string>(c.card_types);

	return *this;
}


void Card::vector_type_card()
{


}

vector<string> * Card::get_pointer()
{
	return &card_types;
}


void Card::set_card_type_id(int num)
{
	card_type = &card_types.at(num);
}

string * Card::get_card_type()
{
	return card_type;
}


//method to play card
void Card::play(Player* a_player,Deck* a_deck )
{
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


//create order and add to players orderlist
a_player->issueOrder(OrderAdvanceType, 1,"p1 order", ALLTERRITORIES->at(1).getName(), ALLTERRITORIES->at(2).getName(), 2);

//return card to deck
a_deck->add_card_to_deck_vector(this);


}



Deck::Deck()
{

}

Deck::~Deck()
{
	//delete pointer
	delete(pointer_to_card);//pointer to card
}

Deck::Deck(const Deck & d)
{
	this->deck_vector = *new vector<Card*>(d.deck_vector);
    this->temp_card_holder = new Card(*(d.temp_card_holder));
	this->pointer_to_card = new Card(*(d.pointer_to_card));

}

Deck & Deck::operator=(const Deck & d)
{

	this->deck_vector = *new vector<Card*>( d.deck_vector);
    this->temp_card_holder = new Card(*(d.temp_card_holder));
	this->pointer_to_card = new Card(*(d.pointer_to_card));

	return *this;
}

//method to set initial deck of cards
void Deck::initial_deck()
{
	//add 30 cards to vector, each type has 5 cards
	for (int a = 0; a < 6; a++) {
		for(int b=0; b<5; b++)
		{
			pointer_to_card = new Card;//create Card

			if(b == 0){
				pointer_to_card->set_card_type_id(0);
				deck_vector.push_back(pointer_to_card);
			}
			else if (b == 1) {
				pointer_to_card->set_card_type_id(1);
				deck_vector.push_back(pointer_to_card);
			}
			else if (b == 2) {
				pointer_to_card->set_card_type_id(2);
				deck_vector.push_back(pointer_to_card);
			}
			else if (b == 3) {
				pointer_to_card->set_card_type_id(3);
				deck_vector.push_back(pointer_to_card);
			}
			else if (b == 4) {
				pointer_to_card->set_card_type_id(4);
				deck_vector.push_back(pointer_to_card);
			}
			else {
				pointer_to_card->set_card_type_id(5);
				deck_vector.push_back(pointer_to_card);
			}
		}


	}
}


//method to draw card from deck and return it
Card* Deck::draw()
{
	//draw random card from the remaining deck of cards
	srand(time(NULL));

	//random is from 0 to the size of current deck_vector, [0, size).
	int temp_size = deck_vector.size();
	int temp = (rand() % temp_size);

	temp_card_holder = deck_vector.at(temp);

	//remove this card from the deck vector
	deck_vector.erase(deck_vector.begin() + temp);

	return temp_card_holder;
}

void Deck::add_card_to_deck_vector(Card * one_card)
{
	//add the card to deck_vector
	deck_vector.push_back(one_card);
}



Hand::Hand()
{
}

Hand::~Hand()
{
}

Hand::Hand(const Hand & h)
{
    this->card_vector = *new vector<Card*>(h.card_vector);
	this->hand_vector = *new vector<Card*>( h.hand_vector);

}

Hand & Hand::operator=(const Hand & h)
{
    this->card_vector = *new vector<Card*>(h.card_vector);
	this->hand_vector = *new vector<Card*>(h.hand_vector);

	return *this;
}

void Hand::set_cards_in_hand(Card * a_card)
{
	//add the card into the hand_vector
	hand_vector.push_back(a_card);

}

void Hand::print_hand_vector()
{
	if (hand_vector.size() > 0) {
		cout << "This Hand " << hand_vector.size() << " cards" << endl;
		for (int j = 0; j < hand_vector.size(); j++) {
			cout<< j << " is " << *hand_vector.at(j)->get_card_type() << endl;
		}
	}
	else {
		cout <<" the hand is now empty \n" << endl;
	}
}

void Hand::print_cards_in_hand()
{
	if (card_vector.size() > 0) {
		cout <<" the play cards order is: " << endl;
		//traverse to print all play cards order
		for (int i = 0; i < card_vector.size(); i++) {
			cout << "  # " << i << " is " << *card_vector.at(i)->get_card_type() << endl;
		}
	}
	else {
		cout << "\n the play cards is empty... \n" << endl;
	}
}


void Hand::return_played_card_to_deck(Deck* a_Deck)
{
	//return played cards to deck cards
	//traverse the card_vector
	for (int n = 0; n < card_vector.size(); n++) {
		//add the played card of card_vector to Deck cards
		a_Deck->add_card_to_deck_vector(card_vector.at(n));
	}

}

vector<Card*>* Hand::get_hand_vector()
{
	return &hand_vector;
}

vector<Card*>* Hand::get_vector_to_cards()
{
	return &card_vector;
}

void Hand::remove_card_played_from_hand_vector(Card* r_card)
{
	//traverse the hand cards, find a card with same type as card, then remove it.
	for (int p = 0; p < hand_vector.size(); p++) {
		if (*hand_vector.at(p)->get_card_type() == *r_card->get_card_type()) {
			//find a same type card, then remove, and return.
			hand_vector.erase(hand_vector.begin() + p);
			cout << "removing a " << *r_card->get_card_type() << "card from hand\n"<<  endl;
			return;
		}
	}
}


// Method to overload the << operator to print the hand
ostream & operator << (ostream &out, Hand *hand)
{

    cout<< "\nHand\n";

    //print cards in hand
    hand->print_cards_in_hand();


    return out;
}


// Method to overload the << operator to print the card type
ostream & operator << (ostream &out, Card *card)
{

    cout<< "\Card\n";

    //print cards in hand
    cout<<card->get_card_type()<<endl;


    return out;
}
