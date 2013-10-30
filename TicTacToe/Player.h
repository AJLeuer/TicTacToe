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
    
public:
    Player() {} ;
    string name ;
    SmartXO xorO ;
    
	char getXOChar() { return (char)(xorO.getXO()) ; }
	XO getXO() { return (xorO.getXO()) ; }
    
};


#endif
