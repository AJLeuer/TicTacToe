//
//  main.cpp
//  TicTacToe
//
//  Created by Adam James Leuer on 10/23/13.
//  Copyright (c) 2013 Adam James Leuer. All rights reserved.
//

#include <iostream>
#include "sstream"

#include "Game.h"
#include "Player.h"
//#include "XO.h"

using namespace std ;

int main(int argc, const char * argv[]) {
	
	
    Game *g = new Game(false, "Adam") ;
    g->playSimGame() ;
    cout << g->getGameLog() << endl ;
	
	cout << "trying another..." << endl ;
	
	g->playSimGame() ;
    cout << g->getGameLog() << endl ;
	
	
	 

}

