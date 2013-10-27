//
//  SmartXO.h
//  TicTacToe
//
//  Created by Adam James Leuer on 10/27/13.
//  Copyright (c) 2013 Adam James Leuer. All rights reserved.
//

#ifndef TicTacToe_SmartXO_h
#define TicTacToe_SmartXO_h

#include "XO.h"

class SmartXO {
	
private:
	static vector<int> database ;
	
	XO xo ;
	int id ;
	
public:
	void scanNearby() ;
	
} ;

class SmartXOBoard : public SmartXO {
	
};



#endif
