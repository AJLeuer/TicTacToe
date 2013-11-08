//
//  Player.h
//  TicTacToe
//
//  Created by Adam James Leuer on 10/24/13.
//  Copyright (c) 2013 Adam James Leuer. All rights reserved.
//

#include "XO.h"
#include "SmartXO.h"

#ifndef TicTacToe_Player_h
#define TicTacToe_Player_h

using namespace std ;


struct Player {
private:
    string name ;
	XO xorO ;

public:
	void setXO(XO Xo) {
		this->xorO = Xo ;
	}
	
	XO getXO() { return xorO ; }
	
	char getXOChar() { return SmartXO::getXOChar(xorO); }
	
	void setName(string name) {
		this->name = name ;
	}
	
	string getName() {
		return this->name ;
	}
	
    
};


#endif
