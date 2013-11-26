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

/*
int main(int argc, const char * argv[]) {
	
	srand((unsigned)time(NULL)) ;
	
	unsigned totalGames = 0 ;
    

    Game *g = new Game(true, "Kyle") ;
    
    
	
	g->playGameRtime() ;
	
}
*/

int main(int argc, const char * argv[]) {
	
	srand((unsigned)time(NULL)) ;
    unsigned x ;
    unsigned y ;

    unsigned totalGames = 0 ;
    unsigned playerWins = 0 ;
    unsigned computerWins = 0 ;
    
    Game *g = new Game(true, "Kyle") ;
    
    Player* human = g->getHuman() ;
    Player* computer = g->getAI() ;
    
    for (unsigned i = 0 ; i < 100000 ; i++) {
        g->playGameRtime() ;
    }
	
	
}

