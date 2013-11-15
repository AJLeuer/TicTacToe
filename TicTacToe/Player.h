//
//  Player.h
//  TicTacToe
//
//  Created by Adam James Leuer on 10/24/13.
//  Copyright (c) 2013 Adam James Leuer. All rights reserved.
//
#include <iostream>

#include "XO.h"
#include "SmartXO.h"

#ifndef TicTacToe_Player_h
#define TicTacToe_Player_h

using namespace std ;


class Player {
	
protected:
    string name ;
	XO xorO ;
	bool human ; //is this player human controlled or computer controlled, default behavior is to set to true (if not specified otherwise in constructor arg)
	Location *nextSpace ; //an x and y coordinate that gives signifies the player or random generator's next choice
	Location *lastWritten ;
	unsigned turns = 0 ; //counter
	unsigned wins = 0 ;
	
public:
	Player() ;
	Player(string) ;
	Player(string, bool) ;
	Player(string, XO, bool) ;
	
	
	
	
	void incTurns() { turns++ ; } //increments turns by 1
	void incWins() { wins++ ; }
	void resetTurns() { turns = 0 ; }
	unsigned getTurns() { return this->turns ; }
	unsigned getWins() {return this->wins ; }
	
	void setXO(XO) ;
	XO getXO() { return xorO ; }
	char getXOChar() ;
	
	void setName(string) ;
	string getName() ;
	
	bool isHuman() { return human ; } //else is AI
	
	void setNextSpace(int, int) ;
	Location *getNextSpace() ;
	
	void setLastWritten(int, int) ;
	void setLastWritten(void) {this->lastWritten = nullptr ; }
	Location *getLastWritten() ;
	
};


#endif
