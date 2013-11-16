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
	Player *p0 = g->getPlayer0() ;
	Player *p1 = g->getPlayer1() ;
	
	unsigned p0wins = 0 ;
	unsigned p1wins = 0 ;
	
	g->playGame() ;
	cout << g->getGameLog() << endl ;
	
	
	for (unsigned i = 0 ; i < 100000 ; i++) {
		g->playGame() ;
		if (g->getWinner() == p0) {
            p0wins++ ;
			cout << g->getGameLog() << endl ;
		}
		 
		if (g->getWinner() == p0)
			p0wins++ ;
		else if (g->getWinner() == p1)
			p1wins++ ;
	}
	 
	
	
	cout << p0->getName() << " was " << char(p0->getXO()) << ", " << p1->getName() << " was " << char(p1->getXO()) << endl ;
	cout << p0->getName() << " had " << p0wins << " wins." << endl ;
	cout << p1->getName() << " had " << p1wins << " wins." << endl ;
	


	
}

