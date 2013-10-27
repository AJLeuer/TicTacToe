//
//  Player.h
//  TicTacToe
//
//  Created by Adam James Leuer on 10/24/13.
//  Copyright (c) 2013 Adam James Leuer. All rights reserved.
//

#include "XO.h"

#ifndef TicTacToe_Player_h
#define TicTacToe_Player_h

using namespace std ;


struct Player {
    
public:
    Player() {} ;
    string name ;
    XO xorO ;
    
	char getXO() { return (char)xorO ; }
    
};


#endif
