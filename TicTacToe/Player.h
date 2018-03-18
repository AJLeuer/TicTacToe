//
//  Player.h
//  TicTacToe
//
//  Created by Adam James Leuer on 10/24/13.
//  Copyright (c) 2013 Adam James Leuer. All rights reserved.
//
#include <iostream>


#include "Mark.h"

#ifndef TicTacToe_Player_h
#define TicTacToe_Player_h

using namespace std ;
using Type = Mark::Type;


class Player {
	
protected:
    string name ;
	Type xorO ;
	bool human ; //is this player human controlled or computer controlled, default behavior is to set to true (if not specified otherwise in constructor arg)
    bool randPlayer ; //this player will just use a rand() generator to choose its moves
	Location *nextSpace ; //an x and y coordinate that gives signifies the player or random generator's next choice
	Location *lastWritten ;
	unsigned turns = 0 ; //counter
	unsigned wins = 0 ;
    bool firstP ;
	
public:
	Player() ;
	Player(string) ;
	Player(string, bool) ;
	Player(string, Type, bool) ;
	
	
	
	
	void incTurns() { turns++ ; } //increments turns by 1
	void incWins() { wins++ ; }
	void resetTurns() { turns = 0 ; }
	unsigned getTurns() { return this->turns ; }
	unsigned getWins() {return this->wins ; }
	
	void setXO(Type) ;
	Type getType() { return xorO ; }
	char getXOChar() ;
	
	void setName(string) ;
	string getName() ;
	
	bool isHuman() { return human ; } //else is AI
    void setFirst(bool b) { this->firstP = b ; }
    bool isFirst() { return this->firstP ; }
    void setRandPlayer(bool randm) {this->randPlayer = randm ; }
    bool isRandPlayer() { return this->randPlayer ; }
	
	void setNextSpace(int, int) ;
	Location *getNextSpace() ;
	
	void setLastWritten(int, int) ;
	void setLastWritten(void) {this->lastWritten = nullptr ; }
	Location *getLastWritten() ;
	
};


#endif
