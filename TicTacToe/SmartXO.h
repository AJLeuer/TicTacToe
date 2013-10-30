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

struct location {
	int x, y ;
	int id ;
} ;

class SmartXO {
	
private:
	static vector<int> database ;
	
	XO xo ;
	int id ;
	location xoLocation ;
	
	void setLocation(int, int) ;
	void getLocation() ;
	
public:
	SmartXO(XO) ;
	void scanNearby() ;
	
	
} ;

class SmartXOBoard : public SmartXO {
private:
	int getNum() ;
	SmartXO board[3][3] ;

public:
	void addAtIndx(int, int) ;
	
	
};





#endif
