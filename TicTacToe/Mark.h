//
//  SmartXO.h
//  TicTacToe
//
//  Created by Adam James Leuer on 10/27/13.
//  Copyright (c) 2013 Adam James Leuer. All rights reserved.
//

#include <vector>
#include <iterator>

#include "Location.h"


#ifndef TicTacToe_SmartXO_h
#define TicTacToe_SmartXO_h

using namespace std ;

extern unsigned int iDs ;

class Mark {
    
public:
    enum Type {
        X = 'X',
        O = 'O',
        blank = ' ',
        nullMark = '?' //special case
    };
	
protected:
    
    Type type;
	unsigned id ;
	Location location ;
	bool on_board ; //this smartXO will be placed on the game board
	
	static void flushDatabase() ;
	
public:
    
	Mark() ;
	Mark(Type, int, int, bool) ;
	void scanNearby() ;
	void operator=(Type) ; //note: a type marked as X or O cannot be written again unless it is first marked blank
	
	Location getLocation() ;
	int getID() ;
	Type getType() ;
	static char getMarkType(Type) ;
	
	/*returns array of locations of Mark objects
	 same type (not including blank) as this*/
	static vector<Location>* getAllLocations(Type) ;
	
	/*returns all sXO objects that are
	 on_board and of the specified XO type*/
	static vector<Mark*>* getAllMarksOfType(Type) ;
	
	bool compareTypes(Type, Type) ;
} ;

extern vector<Mark*>* xDatabase ;
extern vector<Mark*>* oDatabase ;


#endif
