//
//  SmartXO.h
//  TicTacToe
//
//  Created by Adam James Leuer on 10/27/13.
//  Copyright (c) 2013 Adam James Leuer. All rights reserved.
//

#include <vector>
#include <iterator>

#include "XO.h"
#include "Location.h"


#ifndef TicTacToe_SmartXO_h
#define TicTacToe_SmartXO_h

using namespace std ;

extern unsigned int iDs ;

class SmartXO {
	
protected:
	
	XO xo ;
	unsigned id ;
	Location location ;
	bool on_board ; //this smartXO will be placed on the game board
	
	static void flushDatabase() ;
	
	
public:
	SmartXO() ;
	SmartXO(XO, int, int, bool) ;
	void scanNearby() ;
	void operator=(XO) ; //note: an smartXO marked as X or O cannot be written again unless it is first marked blank
	
	Location getLocation() ;
	int getID() ;
	XO getXO() ;
	static char getXOChar(XO) ;
	
	vector<Location>* getAllXOType() ; //returns array of locations of smartXO objects same XO type (not including blank) as this
	
	bool compXO(XO, XO) ;
} ;

extern vector<SmartXO*>* xDatabase ;
extern vector<SmartXO*>* oDatabase ;


#endif
