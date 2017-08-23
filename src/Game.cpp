/*
 * Game.cpp
 *
 *  Created on: Nov 21, 2016
 *      Author: mizrahia
 */
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
#include "../include/Player.h"
#include "../include/Deck.h"
#include "../include/Game.h"
#include "../include/Card.h"

using namespace std;

Game::Game(char* configurationFile):players(),deck(),verbal(),highestnum(),winner(),turncount(),win(),cf()
{
	cf = configurationFile;
	verbal = 0;
	winner = false;
	highestnum = 0;
	turncount = 0;
}

Game::Game(const Game &other):players(),deck(),verbal(other.verbal),highestnum(other.highestnum),winner(other.winner),turncount(other.turncount),win(other.win),cf(other.cf)
{
	Copy(other);
}

Game& Game::operator=(const Game& other)
{
	if(this != &other)
		Copy(other);
	return *this;
}

void Game::Copy(const Game &other)
{
	vector<Player*> othert(other.players);
	Player* p;
	for ( vector<Player*>::iterator it = othert.begin(); it != othert.end(); ++it)
	{
		if((*it)->morType() == 1)
			p = new PlayerType1((**it).getName());
		if((*it)->morType() == 2)
			p = new PlayerType2((**it).getName());
		if((*it)->morType() == 3)
			p = new PlayerType3((**it).getName());
		if((*it)->morType() == 4)
			p = new PlayerType4((**it).getName());
		p->Copy((**it).getHand());
		players.push_back(p);
	}
	deck = Deck(other.deck);
}


Game::~Game()
{
	for (vector<Player*>::iterator it = players.begin(); it != players.end(); ++it)
	{
		delete *it;
	}
}

void Game::init()
{
	  winner=false;
	  win="";
	  turncount=0;
	  string line;
	  ifstream myfile (cf);
	  int counter = 0;
	  if (myfile.is_open())
	  {
		while(getline (myfile,line))
		{
			if(!line.empty() && line.at(0) != '#' && counter == 0)
			{
				if(line == "0")
					verbal = 0;
				else if(line == "1")
					verbal = 1;
				counter++;
			}
			else if(!line.empty() && line.at(0) != '#' && counter == 1)
			{
				highestnum = atoi(line.c_str());
				counter++;
			}
			else if(!line.empty() && line.at(0) != '#' && counter == 2)
			{
				istringstream iss(line);
				vector<string> de;
				copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(de));
				stack<Card*> ddd;
				Deck* deck2 = new Deck(ddd);
				Card* card;
				for(vector<string>::const_iterator it = de.begin(); it != de.end(); it++)
				{
					Shape sh;
					Figure fi;
					int nu;
					char c = (it->substr((*it).length() - 1)).c_str()[0];
					switch(c)
					{
						case 'C':	sh = Club; break;
						case 'D':   sh = Diamond; break;
						case 'H': 	sh = Heart; break;
						case 'S': 	sh = Spade; break;
					}
					c = (it->substr((*it).length()-2)).c_str()[0];

					switch(c)
					{
						case 'J':	fi = Jack; card = new FigureCard(sh,fi); break;
						case 'Q':   fi = Queen; card = new FigureCard(sh,fi); break;
						case 'K': 	fi = King; card = new FigureCard(sh,fi); break;
						case 'A': 	fi = Ace; card = new FigureCard(sh,fi); break;
						default:	nu = atoi((it->substr(0, ((*it).length())-1)).c_str()); card = new NumericCard(sh,nu); break;
					}
					deck2->addToDeck(card);
				}
				counter++;

				int ds = deck2->getDeck().size();
				for(int i=0;i<ds;i++)
				{
					deck.addToDeck(deck2->fetchCard());
				}
				delete deck2;
			}
			else if(!line.empty() && line.at(0) != '#' && counter == 3)
			{
					Player* player;
					istringstream iss(line);
					vector<string> pl;
					copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(pl));
					if(pl[1] == "1")
						player = new PlayerType1(pl[0]);
					if(pl[1] == "2")
						player = new PlayerType2(pl[0]);
					if(pl[1] == "3")
						player = new PlayerType3(pl[0]);
					if(pl[1] == "4")
						player = new PlayerType4(pl[0]);
					players.push_back(player);
			}
		}
		myfile.close();
	  }
	  else cout << "Unable to open file";

	  for (vector<Player*>::iterator it = players.begin() ; it != players.end(); it++)
	  {
		  if((**it).morType() == 3 || (**it).morType() == 4)
			  (*it)->initFromPlace(players.begin());

		  for(int i = 0; i < 7; i++)
		  {
			  (*it)->addCard(*deck.fetchCard());
		  }
	  }
}

Player* Game::fromPlayer(Player* p)
{
	if(p->morType()==1 || p->morType()==2)
	{
		int max=0;
		vector<Player*>::reverse_iterator maxit;
		for (vector<Player*>::reverse_iterator it = players.rbegin() ; it != players.rend(); it++)
		{
			if((**it).getNumberOfCards() > max && (**it).toString() != p->toString())
			{
				max = (**it).getNumberOfCards();
				maxit = it;
			}
		}
		return *maxit;
	 }
	else if(p->morType()==3 || p->morType()==4)
	{
		if(p->getFromPlace() == players.end())
			p->initFromPlace(players.begin());
		if((**(p->getFromPlace())).toString() == p->toString())
		{
			p->setFromPlace();
			if(p->getFromPlace() == players.end())
				p->initFromPlace(players.begin());
		}
		Player* pt = *(p->getFromPlace());
		p->setFromPlace();
		return pt;
	}
	return NULL;
}

void Game::play()
{
	bool b;
	for(unsigned int i = 0; winner == false ; i++)
	{
		b = true;
		bool taken = false;
		int count = 0;
		turncount++;
		printNumberOfTurns();
	    printState();
		Card* want = players[i]->Iwant();
		Player* from = fromPlayer(players[i]);
		cout << players[i]->getName() + " asked " + from->getName() + " for the value " + want->toGive() << endl;
		int cardnum = players[i]->getNumberOfCards();
		while(b == true && count < 3 && players[i]->getNumberOfCards() >= cardnum)
		{
			list<Card*>::iterator junk = from->search(*want);
			Card* c1;
			if(*junk != *from->getHand().end())
				c1 = *junk;
			else
			{
				c1 = *--junk;
			}
			Card* c2 = c1;
			if(c1->equals((**from->getHand().begin())) != 0)
				c2 = *(--from->search(*want));
			b = from->removeCard(*want);
			if(b == true)
			{
				if(from->getNumberOfCards()!= 0 && deck.getNumberOfCards() > 0)
					from->addCard(*deck.fetchCard());
				taken = true;
				if(want->Getnum() == c1->Getnum())
					players[i]->addCard(*c1);
				else
					players[i]->addCard(*c2);
			}
			else if(!taken && deck.getNumberOfCards() > 0)
				players[i]->addCard(*deck.fetchCard());

			if (players[i]->getNumberOfCards() == 0 && from->getNumberOfCards() == 0)
			{
				string winner1 = "";
				string winner2 = "";
				for (vector<Player*>::iterator it = players.begin(); it != players.end() && winner2 == ""; it++)
				{
					if(((**it).getNumberOfCards() == 0) &&( winner1 == ""))
						winner1 = (**it).getName();
					else if((**it).getNumberOfCards() == 0)
							winner2 = (**it).getName();
				}
				cout << "" << endl;
				win="***** The Winners are: " + winner1 + " and " + winner2 + " *****";
				winner = true;
				break;
			}
			else if (players[i]->getNumberOfCards() == 0)
			{
				cout << "" << endl;
				win="***** The Winner is: " + players[i]->getName() + " *****";
				winner = true;
				break;
			}
			else if (from->getNumberOfCards() == 0)
			{
				cout << "" << endl;
				win="***** The Winner is: " + from->getName() + " *****";
				winner = true;
				break;
			}
			count++;
		}

		if(i == players.size()-1)
			i = -1;
	}

}
void Game::printState()
{
	cout <<"Deck: " + deck.toString()<< endl;
	for (vector<Player*>::iterator it = players.begin(); it != players.end(); it++)
	{
		cout <<(**it).toString()<< endl;
	}
}

void Game:: printWinner()
{
	if (verbal==1)
		cout << win << endl;
}

void Game::printNumberOfTurns()
{
	cout << endl;
	cout << "Number of turns: " << turncount << endl;
}

int Game::getVerbal()
{
	return verbal;
}

int Game::getHighestNum()
{
	return highestnum;
}

vector<Player*> Game::getPlayer()
{
	return players;
}

stack<Card*> Game::getDeck()
{
	return deck.getDeck();
}

