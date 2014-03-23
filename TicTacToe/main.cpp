//
//  main.cpp
//  TicTacToe
//
//  Created by Adam James Leuer on 10/23/13.
//  Copyright (c) 2013 Adam James Leuer. All rights reserved.
/*
 This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <time.h>
#include "sstream"

#include "Game.h"
#include "Player.h"
#include "Util.h"

using namespace std ;


int main(int argc, const char * argv[]) {
	
	srand((unsigned)time(NULL)) ;
	
	unsigned totalGames = 0 ;
    

    Game *g = new Game(true, "Nancy") ;
    
	
	g->playGameRtime() ;
	
}

/*

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
 
*/

