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


#ifndef TicTacToe_SmartXO_h
#define TicTacToe_SmartXO_h

using namespace std ;

extern unsigned int iDs ;

class Location {
public:
	int x, y ;
	Location();
} ;

class SmartXO {
	
protected:
	
	XO xo ;
	int id ;
	Location location ;
	
	
	bool compXO(XO, XO) ;
	
public:
	SmartXO() ;
	SmartXO(XO, int, int) ;
	void cleanDB() ; //deletes changed XOs from its database (x or o)
	void scanNearby() ;
	void operator=(XO) ;
	
	Location getLocation() ;
	int getID() ;
	XO getXO() ;
	static char getXOChar(XO) ;
	
	vector<Location>* getAllXOType() ; //returns array of locations of smartXO objects same XO type (not including blank) as this
	
} ;

extern vector<SmartXO*> xDatabase ;
extern vector<SmartXO*> oDatabase ;


#endif
