/*
 * Card.h
 *
 *  Created on: Nov 17, 2016
 *      Author: mizrahia
 */
#ifndef CARD_H_
#define CARD_H_

#include <iostream>

using namespace std;

enum Shape {
	Club,
	Diamond,
	Heart,
	Spade
};

enum Figure {
	Jack,
	Queen,
	King,
	Ace
};

class Card {
private:
  Shape shape;
public:
  virtual string toString() = 0;
  Card(Shape s);
  virtual ~Card();
  virtual int equals(Card &c1);
  virtual int Getnum();
  virtual string shapename();
  virtual Shape Getshape();
  virtual Figure Getfigure();
  virtual string toGive();
};

class FigureCard : public Card {
private:
	Figure figure;
	int number;
public:
	virtual string toString() override;
	FigureCard(Shape s,Figure f);
	virtual ~FigureCard();
	int equals(Card &c1) override;
	int Getnum() override;
	Figure Getfigure() override;
	string toGive() override;
};

class NumericCard : public Card {
private:
	int number;
public:
	virtual string toString() override;
	NumericCard(Shape s,int num);
	virtual ~NumericCard();
	int equals(Card &c1) override;
	int Getnum() override;
	string toGive() override;
};

#endif
