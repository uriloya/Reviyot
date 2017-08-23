/*
 * Player.cpp
 *
 *  Created on: Nov 19, 2016
 *      Author: mizrahia
 */

#include <vector>
#include <iostream>
#include <string>
#include "../include/Card.h"
#include "../include/Hand.h"
#include "../include/Player.h"
#include <list>

using namespace std;
Player::Player(string n):Hand(),name(n),fromplace(){}

Player& Player::operator=(const Player& other)
{
	if(this != &other)
	{
		*this = other;
	}
	return *this;
}

Player::~Player(){}

string Player::getName()
{
	return name;
}

Card* Player::Iwant()
{
	return *--getHand().end();
}
string Player::toString()
{
	return name;
}

int Player::morType()
{
	return 0;
}

vector<Player*>::iterator Player::getFromPlace()
{
	return fromplace;
}

void  Player::setFromPlace()
{
	fromplace++;
}

void Player:: initFromPlace(vector<Player*>::iterator p)
{
	fromplace = p;
}


//PlayerType1

PlayerType1::PlayerType1(string n):Player(n){}

PlayerType1::~PlayerType1(){}

Card* PlayerType1::Iwant()
{
	Card* max = *--getHand().end();
	Card* prev = *--getHand().end();
	int countmax = 0;
	int count = 0;
	list<Card*> lst = getHand();
	for (list<Card*>::reverse_iterator it = lst.rbegin(); it != lst.rend(); it++)
	{
		if((*it)->Getnum() == max->Getnum())
		{
			countmax++;
			count=0;
		}
		else if((*it)->Getnum() == prev->Getnum())
		{
			count++;
		}
		else
		{
			count = 1;
		}

		if (count > countmax)
		{
			max = *it;
			countmax = count;
			count=0;
		}

		prev = *it;
	}
	return max;
}

string PlayerType1::toString()
{
	return getName() + ": " + Hand::toString();
}

 int PlayerType1::morType()
 {
	 return 1;
 }


// PlayerType2

PlayerType2::PlayerType2(string n):Player(n){}

PlayerType2::~PlayerType2(){}

Card* PlayerType2::Iwant()
{
	int countnext=0;
	int countmin=0;
	bool br=true;
	list<Card*> lst = Hand::getHand();
	list<Card*>::iterator it;
	list<Card*>::iterator min = lst.begin();
	list<Card*>::iterator temp = lst.begin();

	for (list<Card*>::iterator it = lst.begin(); it != lst.end()&&br; it++)
	{
		if((**temp).Getnum() == (**it).Getnum())
			countmin++;
		else
		{
			br = false;
		}
		temp = it;
	}
	temp = lst.begin();
	for ( it = lst.begin(); it != lst.end(); it++)
	{
		while( it != lst.end() && (**temp).Getnum() == (**it).Getnum())
		{
			countnext++;
			it++;
		}
		temp=it;
		if(countnext < countmin)
		{
			countmin = countnext;
			countnext = 0;
			min = --it;
		}
		else
			it--;
		countnext=0;
	}
	return (*min);
}

string PlayerType2::toString()
{
	return getName() + ": " + Hand::toString();
}


int PlayerType2::morType()
{
	 return 2;
}


// PlayerType3

PlayerType3::PlayerType3(string n):Player(n),fromplace(){}

PlayerType3::~PlayerType3(){}

Card* PlayerType3::Iwant()
{
	return *--getHand().end();
}

string PlayerType3::toString()
{
	return getName() + ": " + Hand::toString();
}

vector<Player*>::iterator PlayerType3::getFromPlace()
{
	return fromplace;
}

void  PlayerType3::setFromPlace()
{
	fromplace++;
}

void PlayerType3:: initFromPlace(vector<Player*>::iterator p)
{
	fromplace = p;
}

int PlayerType3::morType()
{
	 return 3;
}


// PlayerType4

PlayerType4::PlayerType4(string n):Player(n),fromplace(){}

PlayerType4::~PlayerType4(){}

Card* PlayerType4::Iwant()
{
	return *getHand().begin();
}

string PlayerType4::toString()
{
	return getName() + ": " + Hand::toString();
}

vector<Player*>::iterator PlayerType4::getFromPlace()
{
	return fromplace;
}

void  PlayerType4::setFromPlace()
{
	fromplace++;
}

void PlayerType4:: initFromPlace(vector<Player*>::iterator p)
{
	fromplace = p;
}

int PlayerType4::morType()
{
	 return 4;
}




