#ifndef DECK_H_
#define DECK_H_

#include <iostream>
#include <stack>
#include "Card.h"

using namespace std;

class Deck
{
	private:
		stack<Card*> deck;
	public:
		Deck();
		Deck(stack<Card*> de);
		void Copy(const Deck &other);
		Deck& operator=(const Deck &other);
		Deck(const Deck &other );
		~Deck();
		Card* fetchCard();   //Returns the top card of the deck and remove it rom the deck
		int getNumberOfCards(); // Get the number of cards in the deck
		void addToDeck(Card* card); //adds card to deck
		string toString(); // Return the cards in top-to-bottom order in a single line, cards are separated by a space ex: "12S QD AS 3H"
		stack<Card*> getDeck();
};

#endif
