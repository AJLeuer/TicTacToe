//
//  main.cpp
//  TicTacToe
//
//  Created by Adam James Leuer on 10/23/13.
//  Copyright (c) 2013 Adam James Leuer. All rights reserved.
//

#include <iostream>
#include <time.h>
#include "sstream"

#include "Game.h"
#include "Player.h"
#include "Util.h"

using namespace std ;

int main(int argc, const char * argv[]) {
	
	srand((unsigned)time(NULL)) ;
	bool b = (rand() % 2) ;
	bool b2 = (rand() % 2) ;
	
	unsigned totalGames = 0 ;

    Game *g = new Game(true, "Guy") ;
	
	g->playGameRtime() ;
	
}

