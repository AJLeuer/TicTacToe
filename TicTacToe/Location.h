//
//  Location.h
//  TicTacToe
//
//  Created by Adam James Leuer on 11/10/13.
//  Copyright (c) 2013 Adam James Leuer. All rights reserved.
//

#ifndef TicTacToe_Location_h
#define TicTacToe_Location_h

class Location {
public:
	int x, y ;
	Location();
	Location(int x, int y) { this->x = x ; this->y = y ; }
} ;


#endif