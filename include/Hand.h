#ifndef HAND_H_
#define HAND_H_

#include <iostream>
#include <list>
#include <string>
#include "Card.h"

using namespace std;

class Hand
{
	private:
		list<Card*> hand;
	public:
		Hand(list<Card*> l);
		Hand(const Hand &other);
		Hand();
		Hand& operator=(const Hand &other);
		void Copy(const Hand &other);
		void Copy(list<Card*> l);
		virtual ~Hand();
		list<Card*>::iterator search(Card &card);
		void hasFour(Card &card);
		bool addCard(Card &card);
		bool removeCard(Card &card);
		list<Card*> getHand();
		int getNumberOfCards();
		string toString();
};

#endif
