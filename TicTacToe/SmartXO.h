//
//  SmartXO.h
//  TicTacToe
//
//  Created by Adam James Leuer on 10/27/13.
//  Copyright (c) 2013 Adam James Leuer. All rights reserved.
//

#include <vector>
#include "XO.h"


#ifndef TicTacToe_SmartXO_h
#define TicTacToe_SmartXO_h

using namespace std ;

class Location {
public:
	int x, y ;
	Location();
} ;

class SmartXO {
	
protected:
	static int count ;
	static int iDs ;
	static vector<SmartXO*> xDatabase ;
	static vector<SmartXO*> oDatabase ;
	
	
	XO xo ;
	int id ;
	Location location ;
	
	
	bool compXO(XO, XO) ;
	
public:
	SmartXO() ;
	SmartXO(XO, int, int) ;
	void scanNearby() ;
	void operator=(XO) ;
	
	Location getLocation() ;
	int getID() ;
	XO getXO() ;
	
	vector<Location>* getAllXOType() ; //returns array of locations of smartXO objects same XO type (not including blank) as this
	
	
} ;


#endif
