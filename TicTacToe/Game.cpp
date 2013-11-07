//
//  Game.cpp
//  TicTacToe
//
//  Created by Adam James Leuer on 10/23/13.
//  Copyright (c) 2013 Adam James Leuer. All rights reserved.
//

#include <sstream>
#include <iostream>
#include <time.h>

#include "Game.h"

using namespace std ;

Game::Game() { //best for ai v ai
    srand((unsigned)time(NULL)) ;
	winner = false ;
	plyrActnCode = 3 ;
	gamesPlayed = 0 ;
	boardSize = sizeof(board)/sizeof(board[0]) ;
    rowSize = sizeof(board[0])/sizeof(board[0][0]) ;
    setStarted(false) ;
    currentGameLog = new stringstream() ;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0 ; j < rowSize; j++) {
            board[i][j] = new SmartXO(blank, i, j) ;
        }
    }
    initPlayers() ;
}

Game::Game(bool player0WantsX, string p0Name) { //p v ai
    srand((unsigned)time(NULL)) ;
	winner = false ;
	plyrActnCode = 3 ;
	gamesPlayed = 0 ;
	boardSize = sizeof(board)/sizeof(board[0]) ;
    rowSize = sizeof(board[0])/sizeof(board[0][0]) ;
    setStarted(false) ;
    currentGameLog = new stringstream() ;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0 ; j < rowSize; j++) {
            board[i][j] = new SmartXO(blank, i, j) ;
        }
    }
    initPlayers(player0WantsX, p0Name, "Computer") ;
}

Game::Game(bool player0WantsX, string p0Name, string p1Name) { //pvp
    srand((unsigned)time(NULL)) ;
	winner = false ;
	plyrActnCode = 3 ;
	gamesPlayed = 0 ;
	boardSize = sizeof(board)/sizeof(board[0]) ;
    rowSize = sizeof(board[0])/sizeof(board[0][0]) ;
    setStarted(false) ;
    currentGameLog = new stringstream() ;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0 ; j < rowSize; j++) {
            board[i][j] = new SmartXO(blank, i, j) ;
        }
	}
    initPlayers(player0WantsX, p0Name, p1Name) ;
}

void Game::initPlayers() { //auto-inits with preset names
    initPlayers("Player0", "Player1") ;
}

void Game::initPlayers(string p0Name, string p1Name) {
    bool player0WantsX = rand() % 2 ;
    initPlayers(player0WantsX, p0Name, p1Name) ;
}

void Game::initPlayers(bool player0WantsX, string p0Name, string p1Name) {
    player0 = new Player() ;
    player1 = new Player() ;
    
    player0->name = p0Name ;
    player1->name = p1Name ;
    
    bool player0First = rand() % 2 ;
	if (player0First) {
		currentPlayer = player0 ;
		nextPlayer = player1 ;
	}
	else {
		currentPlayer = player1 ;
		nextPlayer = player0 ;
	}
	
    player0IsX = player0WantsX ;
    if (player0IsX) {
        player0->xorO = X ;
        player1->xorO = O ;
    }
    else {
        player0->xorO = O ;
        player1->xorO = X ;
    }
    
}


/* Set true if we've started a game
 */
void Game::setStarted(bool st) {
    started = st ;
	gameOver = (!st) ;
}

bool Game::checkSetCompleted() {
    bool allWritten = true ;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0 ; j < rowSize; j++) {
            if (!(isWritten(i, j))) {
				allWritten = false ;
			}
        }
    }
	return allWritten ;
}

bool Game::checkStarted() {
    return started ;
}

char Game::getIndex(int x, int y) {
    return (char)(((board[x][y]))->getXO()) ;
}

XO Game::getIndexAsXO(int x, int y){
	return (((board[x][y]))->getXO()) ;
}

bool Game::isWritten(int x, int y) {
    if (((((board[x][y]))->getXO()) == X) || ((((board[x][y]))->getXO()) == O)) {
		return true ;
	}
    return false ;
}

void Game::writeIndex(int x, int y, XO inp) {
    *(board[x][y]) = inp ;
}

void Game::writeAllIndex(XO xorO) {
	for (int i = 0 ; i < boardSize; i++) {
        for (int j = 0 ; j < rowSize; j++) {
			writeIndex(i, j, xorO) ;
		}
	}
}

void Game::resetGame() {
	gamesPlayed++ ;
	setStarted(false) ; //will set gameOver state as well
	winner = false ;
	plyrActnCode = 3 ;
	writeAllIndex(blank) ;
	if (winPlayer == player0) {
		currentPlayer = player0 ;
		nextPlayer = player1 ;
	}
	else {
		currentPlayer = player1 ;
		nextPlayer = player0 ;
	}
}


void Game::playerAction(int x, int y) {
    if (checkSetCompleted()) {
		plyrActnCode = 2 ;
	}
	else if (isWritten(x, y)) {
		plyrActnCode = 1 ;
	}
	else if (!(isWritten(x, y))) {
		writeIndex(x, y, currentPlayer->getXO()) ;
		tempPlayer = currentPlayer ;
		currentPlayer = nextPlayer ;
		nextPlayer = tempPlayer ;
		if (checkSetCompleted()) {
			plyrActnCode = 2 ; //should end this game
		}
		else {
			plyrActnCode = 0 ;
		}
	}
}

void Game::nextGameEvent(int x, int y) {
    if (!(checkStarted())) {
        setStarted(true) ;
		*currentGameLog << "New Game!" << endl ;
		if (gamesPlayed == 0) {
			*currentGameLog << player0->name <<  " is " << player0->getXO() << "." << endl ;
			*currentGameLog << player1->name <<  " is " << player1->getXO() << "." << endl ;
			*currentGameLog << currentPlayer->name << " goes first!" << endl ;
		}
		else {
			*currentGameLog << "Since " << currentPlayer->name << " won last, " << currentPlayer->name << " goes first!" << endl ;
		}
		*currentGameLog << nextPlayer->name << " goes second!" << endl << endl <<endl ;
    }
	
	playerAction(x, y) ;
	
	//temp for debugging - todo remove
	writeIndex(0, 0, O) ;
	writeIndex(1, 1, O) ;
	writeIndex(2, 2, O) ;
	
	string s = toString() ;
	//end temp
	
	checkWin() ;
	
	if ((plyrActnCode == 0) && (!(winner == true))) {
		*currentGameLog << toString() << endl << endl  ;
	}
	else if (plyrActnCode == 1) {
		; //that index was written, we'll try again
	}
	else if (plyrActnCode == 3) {
		cout << "Problem with playerAction() function. debug" << endl ;
		throw new exception() ;
	}
	if ((plyrActnCode == 2) || (winner == true)) {
		*currentGameLog << toString() << endl << endl  ;
		*currentGameLog << winPlayer->name << " wins! Game over!" << endl << endl ;
		
		//string s = toString() ; //remove this
		
		resetGame() ;
	}
}

void Game::playSimGame() {
	while(true) {
		int x = rand() % 3 ;
		int y = rand() % 3 ;
		nextGameEvent(x, y) ;
		if (gameOver) {
			break ;
		}
	}
}

void Game::playGameRtime() {
	currentGameLog = &cout ;
	//todo implement
	//code
}

void Game::checkWin() {
	bool won = checkLocations() ;
	winPlayer = player0 ;
	winner = won ;
}

bool Game::checkLocations() {
	bool ret = false ;
    for (int i = 0 ; i < boardSize ; i++) {
		if (((board[i][0])->getXO()) != blank) {
			if (((board[i][0])->getAllXOType()) != nullptr) {
				Location here = (board[i][0])->getLocation() ;
				//<-
				vector<Location> *elsewhere = (board[i][0])->getAllXOType() ;
				ret = findPattern(here, elsewhere, direction::null, 0) ;
				if (ret == true) {
					return ret ;
				}
			}
		}
    }
	for (int i = 0 ; i < rowSize ; i++) {
		if (((board[0][i])->getXO()) != blank) {
			if (((board[0][i])->getAllXOType()) != nullptr) {
				Location here = (board[0][i])->getLocation() ;
				vector<Location> *elsewhere = (board[0][i])->getAllXOType() ;
				ret = findPattern(here, elsewhere, direction::null, 0) ;
				if (ret == true) {
					return ret ;
				}
			}
		}
    }
	return ret ;
}

bool Game::findPattern(Location here, vector<Location>* elseWhere, direction d, int chainSize) {
	
	//string s = this->toString() ;  //remove this
	
    if (chainSize >= boardSize) {
        return true ;
    }
	if ((d == direction::null) || (d == direction::right)) { // then search right next...
		Location *loc = (locSearch(here, elseWhere, 1, 0)) ;
		if (loc != nullptr) {
			return findPattern(*loc, elseWhere, direction::right, (chainSize + 1)) ;
		}
	}
	if ((d == direction::null) || (d == direction::left)) {
		Location *loc = (locSearch(here, elseWhere, -1, 0)) ;
		if (loc != nullptr) {
			return findPattern(*loc, elseWhere, direction::left, (chainSize + 1)) ;
		}
	}
	if ((d == direction::null) || (d == direction::up)) {
		Location *loc = (locSearch(here, elseWhere, 0, -1)) ;
		if (loc != nullptr) {
			return findPattern(*loc, elseWhere, direction::up, (chainSize + 1)) ;
		}
	}
	if ((d == direction::null) || (d == direction::down)) {
		Location *loc = (locSearch(here, elseWhere, 0, 1)) ;
		if (loc != nullptr) {
			return findPattern(*loc, elseWhere, direction::down, (chainSize + 1)) ;
		}
	}
	if ((d == direction::null) || (d == direction::upRight)) {
		Location *loc = (locSearch(here, elseWhere, 1, -1)) ;
		if (loc != nullptr) {
			return findPattern(*loc, elseWhere, direction::upRight, (chainSize + 1)) ;
		}
	}
	if ((d == direction::null) || (d == direction::upLeft)) {
		Location *loc = (locSearch(here, elseWhere, -1, -1)) ;
		if (loc != nullptr) {
			return findPattern(*loc, elseWhere, direction::upLeft, (chainSize + 1)) ;
		}
	}
	if ((d == direction::null) || (d == direction::downRight)) {
		Location *loc = (locSearch(here, elseWhere, 1, 1)) ;
		if (loc != nullptr) {
			return findPattern(*loc, elseWhere, direction::downRight, (chainSize + 1)) ;
		}
	}
	if ((d == direction::null) || (d == direction::downLeft)) {
		Location *loc = (locSearch(here, elseWhere, -1, 1)) ;
		if (loc != nullptr) {
			return findPattern(*loc, elseWhere, direction::downLeft, (chainSize + 1)) ;
		}
	}
	return false ;
}

Location* Game::locSearch(Location here, vector<Location>* elseWhere, int x_offset, int y_offset) {
	Location *loc = nullptr ;
	for (vector<Location>::size_type i = 0 ; i < elseWhere->size() ; i++) {
		if(((elseWhere->at(i).x) == (here.x + x_offset)) && ((elseWhere->at(i).y) == (here.y + y_offset))) {
			loc = &(elseWhere->at(i)) ;
		}
	}
	return loc ;
}

string Game::toString() {
    stringstream *gameString = new stringstream() ;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0 ; j < rowSize; j++) {
            if (j == 0) {
				*gameString << getIndex(i, j) ;
			}
            if ((j > 0) && (j < (rowSize - 1))) {
                if (getIndex(i, j) == ' ') {
					*gameString << " |" << getIndex(i, j) << " |" ;
				}
                else {
					*gameString << " | " << getIndex(i, j) << "|" ;
				}
            }
            if (j == (rowSize - 1)) {
				*gameString << getIndex(i, j) << endl ;
			}
        }
        if (i < (boardSize - 1)) {
            *gameString << "-- -- --" ;
            *gameString << endl ;
        }
        if (i == (boardSize - 1)) {
			*gameString << endl ;
		}
    }
    return gameString->str() ;
}

string Game::getGameLog() {
	stringstream *tempLog = new stringstream() ;
	*tempLog << currentGameLog->rdbuf() ;
    return tempLog->str() ;
}



