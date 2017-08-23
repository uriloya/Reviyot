/*
 * Player.h

 *
 *  Created on: Nov 19, 2016
 *      Author: mizrahia
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <string>
#include "Card.h"
#include "Hand.h"
#include <vector>

using namespace std;

class Player : public Hand
{
private:
	const string name;
	vector<Player*>::iterator fromplace;
public:
	Player (string n);
	Player& operator=(const Player& other);
	virtual ~Player();
	string getName();
	virtual Card* Iwant();
	virtual string toString();
	virtual vector<Player*>::iterator getFromPlace();
	virtual void setFromPlace();
	virtual int morType();
	virtual void initFromPlace(vector<Player*>::iterator p);
};

class PlayerType1 : public Player
{
public:
	PlayerType1(string n);
	virtual ~PlayerType1();
	virtual Card* Iwant() override;
	virtual string toString() override;
	virtual int morType();
};

class PlayerType2 : public Player
{
public:
	PlayerType2(string n);
	virtual ~PlayerType2();
	virtual Card* Iwant() override;
	virtual string toString() override;
	virtual int morType();
};

class PlayerType3 : public Player
{
private:
	vector<Player*>::iterator fromplace;
public:
	PlayerType3(string n);
	virtual ~PlayerType3();
	virtual Card* Iwant() override;
	virtual string toString() override;
	virtual vector<Player*>::iterator getFromPlace();
	virtual void setFromPlace();
	virtual void initFromPlace(vector<Player*>::iterator p);
	virtual int morType();
};

class PlayerType4 : public Player
{
private:
	vector<Player*>::iterator fromplace;
public:
	PlayerType4(string n);
	virtual ~PlayerType4();
	virtual Card* Iwant() override;
	virtual string toString() override;
	virtual vector<Player*>::iterator getFromPlace();
	virtual void setFromPlace();
	virtual void initFromPlace(vector<Player*>::iterator p);
	virtual int morType();
};

#endif
