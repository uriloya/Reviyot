
#include <iostream>
#include <stack>
#include "../include/Card.h"
#include "../include/Deck.h"

using namespace std;
Deck::Deck():deck(){}

Deck& Deck::operator=(const Deck &other)
{
	if(this != &other)
	{
		Copy(other);
	}
	return *this;
}

void Deck::Copy(const Deck &other)
{
	stack<Card*> other2 = other.deck;
	stack<Card*> temp;
	int length = other2.size();
	for(int i=0;i<length;i++)
	{
		temp.push(other2.top());
		other2.pop();
	}
	for(int i=0;i<length;i++)
	{
		Card* c = temp.top();
		if(c->Getnum() < 0 )
			c = new FigureCard(c->Getshape(),c->Getfigure());
		else
			c = new NumericCard(c->Getshape(), c->Getnum());
		deck.push(c);
		temp.pop();
	}
}

Deck::Deck(stack<Card*> d):deck(d){}

Deck::Deck(const Deck &other):deck()
{
	Copy(other);
}

Deck::~Deck()
{
	while(!deck.empty())
	{
		delete(deck.top());
		deck.pop();
	}
}

Card* Deck::fetchCard()
{
	Card* ctemp;
	if(!deck.empty())
	{
		ctemp = deck.top();
		deck.pop();
	}
	else
		return NULL;
	return ctemp;
}

int Deck::getNumberOfCards()
{
	return deck.size();
}

void Deck::addToDeck(Card* card)
{
	deck.push(card);
}

string Deck::toString()
{
	stack<Card*> temp;
	string st="";
	int ds = deck.size();
	for(int i=0;i<ds;i++)
	{
		st= st+deck.top()->toString()+" ";
		temp.push(deck.top());
		deck.pop();
	}
	for(int i=0;i<ds;i++)
	{
		deck.push(temp.top());
		temp.pop();
	}
	return st;
}
stack<Card*> Deck::getDeck()
{
	return deck;
}

