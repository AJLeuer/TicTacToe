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
	
	pause(2) ;
	
	cout << "Hi" << endl ;
	
	
	cout << "hey" << endl ;

    Game *g = new Game(false, true, false, "Adam") ;
	
	g->playGameRtime() ;
	
    g->playSimGame() ;
	
 
	
/*
    cout << g->getGameLog() << endl ;
	
	cout << "trying another..." << endl ;
	
	g->playSimGame() ;
    cout << g->getGameLog() << endl ;
*/
	
}

