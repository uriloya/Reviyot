#include <iostream>
#include <list>
#include "../include/Card.h"
#include "../include/Hand.h"

using namespace std;

Hand::Hand(list<Card*> l):hand()
{
	for (list<Card*>::iterator it = l.begin(); it != l.end(); it++)
	{
		Card* c = (*it);
		addCard(*c);
	}
}

Hand::Hand(const Hand &other):hand()
{
	Hand ha = other;
	list<Card*> l = ha.getHand();
	for (list<Card*>::iterator it = l.begin(); it != l.end(); it++)
	{
		Card* c = (*it);
		addCard(*c);
	}
}

Hand::Hand():hand(){}

Hand& Hand::operator=(const Hand &other)
{
	if(this != &other)
	{
		Copy(other);
	}
	return *this;
}

void Hand::Copy(const Hand &other)
{
	list<Card*> l = other.hand;
	for (list<Card*>::iterator it = l.begin(); it != l.end(); it++)
	{
		Card* c = (*it);
		if(c->Getnum() < 0 )
			c = new FigureCard(c->Getshape(),c->Getfigure());
		else
			c = new NumericCard(c->Getshape(), c->Getnum());
		addCard(*c);
	}
}

void Hand::Copy(list<Card*> l)
{
	for (list<Card*>::iterator it = l.begin(); it != l.end(); it++)
	{
		Card* c = (*it);
		if(c->Getnum() < 0 )
			c = new FigureCard(c->Getshape(),c->Getfigure());
		else
			c = new NumericCard(c->Getshape(), c->Getnum());
		addCard(*c);
	}
}

Hand::~Hand()
{
	for (list<Card*>::iterator it = hand.begin(); it != hand.end(); it++)
	{
		delete *it;
	}
}

list<Card*>::iterator Hand::search(Card &card)
{
	for (list<Card*>::iterator it = hand.begin(); it != hand.end(); it++)
	{
		int x = (*it)->equals(card);
		if(x > 0)
		{
			return it;

		}
		else if(x == 0)
		{
			if((*it)->shapename().compare(card.shapename()) > 0 || (*it)->shapename().compare(card.shapename()) == 0 )
				return it;
		}
	}
		return hand.end();
}

void Hand::hasFour(Card &card)
{
	int count4 = 0;
	list<Card*>::iterator it = hand.begin();
	while(it != hand.end() && card.Getnum() != (**it).Getnum())
	{
		it++;
	}
	while(it != hand.end() && card.Getnum() == (**it).Getnum())
	{
		count4++;
		it++;
	}
	it--;
	if(count4 == 4)
	{
		Card* ctemp = *it;
		hand.erase(it--);
		delete ctemp;
		ctemp = *it;
		hand.erase(it--);
		delete ctemp;
		ctemp = *it;
		hand.erase(it--);
		delete ctemp;
		ctemp = *it;
		hand.erase(it);
		delete ctemp;
	}
}


bool Hand::addCard(Card &card)
{
	list<Card*>::iterator it = search(card);
	if(it == hand.end())
	{
		hand.push_back(&card);
		hasFour(card);
		return true;
	}
	else
	{
		hand.insert(it,&card);
		hasFour(card);
	    return true;
	}
	return false;
}


bool Hand::removeCard(Card &card)
{
	list<Card*>::iterator temp = search(card);
	if(temp != hand.end() && (*temp)->Getnum() == card.Getnum())
	{
		hand.erase(temp);
		return true;
	}
	else if(temp != hand.begin() && temp != hand.end() && (*--temp)->Getnum() == card.Getnum())
	{
			hand.erase(temp);
			return true;
	}
	else if(temp == hand.end() && (**--hand.end()).Getnum() == card.Getnum())
	{
			hand.erase(--temp);
			return true;
	}

	return false;
}

list<Card*> Hand::getHand()
{
	return hand;
}

int Hand::getNumberOfCards()
{
	return hand.size();
}

string Hand::toString()
{
	string st = "";
	for (list<Card*>::iterator it = hand.begin(); it != hand.end(); it++)
	{
		st = st + (*it)->toString() + " ";
	}
	return st;
}


