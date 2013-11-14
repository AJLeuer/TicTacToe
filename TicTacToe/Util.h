//
//  Header.h
//  TicTacToe
//
//  Created by Adam James Leuer on 11/13/13.
//  Copyright (c) 2013 Adam James Leuer. All rights reserved.
//

#include <unistd.h>

#ifndef TicTacToe_Header_h
#define TicTacToe_Header_h

void pause(unsigned long seconds)  {
	unsigned long second = 1000000 ;
	usleep(seconds * second) ;
}



#endif
