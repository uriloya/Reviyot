#ifndef GAME_H_
#define GAME_H_
#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <list>

#include "Player.h"
#include "Deck.h"
#include "Card.h"

using namespace std;

class Game {
private:
	vector<Player *> players;  //The list of the players
	Deck deck;
	int verbal;
	int highestnum;
	bool winner;
	int turncount;
	string win;
	char* cf;
public:
	Game(char* configurationFile);
	Game(const Game &other);
	Game& operator=(const Game& other);
	void Copy(const Game &other);
	~Game();
	void init();
    Player* fromPlayer(Player* p);
	void play();
	void printState();
	void printWinner();
    void printNumberOfTurns();
    int getVerbal();
    int getHighestNum();
    stack<Card*> getDeck();
    vector<Player*> getPlayer();

};

#endif
