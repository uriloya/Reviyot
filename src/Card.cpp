/*
 * Card.cpp
 *
 *  Created on: Nov 17, 2016
 *      Author: mizrahia
 */

#include "../include/Card.h"
#include <string>
#include <sstream>

using namespace std;

	Card::Card(Shape s):shape(s){}

	Card::~Card(){}

	int Card::Getnum()
	{
		return 0;
	}

	Figure Card::Getfigure()
	{
		return Ace;
	}

	Shape Card::Getshape()
	{
		return shape;
	}

	int Card::equals(Card &c1)
	{
			return 0;
	}
	string Card::shapename()
	{
		switch (shape)
		{
		    case Club:	return "C";
		    case Diamond:   return "D";
		    case Heart: return "H";
		    case Spade: return "S";
		    default:	return "Z";
		}
	}

	string Card::toString()
	{
		if (shape == Spade) return "S";
		if (shape == Club) return "C";
		if (shape == Diamond) return "D";
		if (shape == Heart) return "H";
		return "Z";
	}

	string Card::toGive()
	{
		if (shape == Spade) return "S";
		if (shape == Club) return "C";
		if (shape == Diamond) return "D";
		if (shape == Heart) return "H";
		return "Z";
	}

	FigureCard::FigureCard(Shape s,Figure f):Card(s),figure(f),number()
	{
		if (figure == Jack) number =-4;
		if (figure == Queen) number =-3;
		if (figure == King) number =-2;
		if (figure == Ace) number =-1;
	}

	FigureCard::~FigureCard(){}

	string FigureCard::toString()
	{
		if (figure == Jack) return "J"+Card::toString();
		if (figure == Queen) return "Q"+Card::toString();
		if (figure == King) return "K"+Card::toString();
		if (figure == Ace) return "A"+Card::toString();
		return "Z";
	}

	string FigureCard::toGive()
	{
		if (figure == Jack) return "J";
		if (figure == Queen) return "Q";
		if (figure == King) return "K";
		if (figure == Ace) return "A";
		return "Z";
	}

	int FigureCard::Getnum()
	{
		return number;
	}

	Figure FigureCard::Getfigure()
	{
		return figure;
	}

	int FigureCard::equals(Card &c1)
		{
			if (c1.Getnum() > 0 || Getnum() > c1.Getnum())
				return 1;
			if (Getnum() < c1.Getnum())
					return -1;
			return 0;
		}

	NumericCard::NumericCard(Shape s,int num):Card(s),number(num){}

	NumericCard::~NumericCard(){}

	string NumericCard::toString()
	{
		stringstream ss;
		ss << number;
		string str = ss.str();
		string st = Card::toString();
		return str+st;
	}

	string NumericCard::toGive()
	{
		stringstream ss;
		ss << number;
		string str = ss.str();
		return str;
	}

	int NumericCard::Getnum()
	{
		return number;
	}


	int NumericCard::equals(Card &c1)
	{
		if (c1.Getnum() < 0 || Getnum() < c1.Getnum())
			return -1;
		if (Getnum() > c1.Getnum())
				return 1;
		return 0;
	}
