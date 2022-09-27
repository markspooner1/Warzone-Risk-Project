#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

class Card {
public:
	Card();

	Card(const Card& c);

	Card& operator = (const Card& c);

    //virtual destructor
	 virtual ~Card();

	//initialize the type vector
	void vector_type_card();

	//pointer to the type vector
	vector<string>* get_pointer();


    string* get_card_type();

	//card type 0-5
	void set_card_type_id(int num);

private:
    string* card_type;

	//this vector stores the 5 types of cards  bomb, reinforcement, blockade,airlift, diplomacy,
	vector<string> card_types = {"bomb", "reinforcement", "blockade", "airlift", "diplomacy"};


};

//deck class inherits from the above card class
class Deck: public Card{

public:
    ~Deck();

	Deck();


	Deck(const Deck& d);


	Deck& operator=(const Deck& d);

	//initial the deck  will have 30 cards in it, 5 of each type
	void initial_deck();


	//draw method to allow a player to draw a card at random from the cards currently in the deck
	Card* draw();

	//the method is to return played cards into deck vector
	void add_card_to_deck_vector(Card* one_card);


private:
	vector<Card*> deck_vector; //deck of cards

	Card* temp_card_holder;//to draw and remove the element of deck vector

	Card* pointer_to_card;

};


//Hand class inherits from the above card class
class Hand :  public Card {

public:
    ~Hand();

	Hand(const Hand& h);

    Hand();

	Hand& operator=(const Hand& h);

	//set cards in hand
	void set_cards_in_hand(Card* a_card);


	void print_cards_in_hand();

	//method that is called to play the card
	void play(Card* a_card, Deck* a_Deck);


	//print hards in hand
	void print_hand_vector();

	//returns a card to the deck card
	void return_played_card_to_deck(Deck* a_Deck);

	//get pointer to cards
	vector<Card*>* get_vector_to_cards();


	vector<Card*>* get_hand_vector();


	//remove the  played card from cards in hand
	void remove_card_played_from_hand_vector(Card* r_card);



private:
	vector<Card*> hand_vector;
	vector<Card*> card_vector;

};
