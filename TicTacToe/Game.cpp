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
	maxSize = ceiling(boardSize, rowSize) ;
	winningXO = nullxo ;
    setStarted(false) ;
    currentGameLog = new stringstream() ;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0 ; j < rowSize; j++) {
            board[i][j] = new SmartXO(blank, i, j, true) ;
        }
    }
    initPlayers() ;
}

Game::Game(string p0Name) {
	srand((unsigned)time(NULL)) ;
	winner = false ;
	plyrActnCode = 3 ;
	gamesPlayed = 0 ;
	boardSize = sizeof(board)/sizeof(board[0]) ;
    rowSize = sizeof(board[0])/sizeof(board[0][0]) ;
	maxSize = ceiling(boardSize, rowSize) ;
	winningXO = nullxo ;
    setStarted(false) ;
    currentGameLog = new stringstream() ;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0 ; j < rowSize; j++) {
            board[i][j] = new SmartXO(blank, i, j, true) ;
        }
    }
    initPlayers(p0Name, "Computer") ;
}

Game::Game(bool player0WantsX, string p0Name) { //p v ai
    srand((unsigned)time(NULL)) ;
	winner = false ;
	plyrActnCode = 3 ;
	gamesPlayed = 0 ;
	boardSize = sizeof(board)/sizeof(board[0]) ;
    rowSize = sizeof(board[0])/sizeof(board[0][0]) ;
	maxSize = ceiling(boardSize, rowSize) ;
	winningXO = nullxo ;
    setStarted(false) ;
    currentGameLog = new stringstream() ;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0 ; j < rowSize; j++) {
            board[i][j] = new SmartXO(blank, i, j, true) ;
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
	maxSize = ceiling(boardSize, rowSize) ;
	winningXO = nullxo ;
    setStarted(false) ;
    currentGameLog = new stringstream() ;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0 ; j < rowSize; j++) {
            board[i][j] = new SmartXO(blank, i, j, true) ;
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
    
    player0->setName(p0Name) ;
    player1->setName(p1Name) ;
    
	winPlayer = nullptr ;
	lastWinner = nullptr ;
	
	
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
        player0->setXO(X) ;
        player1->setXO(O) ;
    }
    else {
        player0->setXO(O) ;
        player1->setXO(X) ;
    }
}

Player* Game::idPlByXO(XO Xo) {
	
	if (player0->getXO() == (Xo)) {
		return player0 ;
	}
	else if(player1->getXO() == (Xo)) {
		return player1 ;
	}
	else {
		cout << "seriously? check the idPlByXO() function" << endl ;
		throw new exception() ;
	}
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

void Game::checkWin() {
	bool won = checkLocations() ;
	if (won) {
		winPlayer = idPlByXO(winningXO) ;
	}
	winner = won ;
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


void Game::nextGameEvent(int x, int y) {
    if (!(checkStarted())) {
        setStarted(true) ;
		*currentGameLog << "New Game!" << endl ;
		if (gamesPlayed == 0) {
			*currentGameLog << player0->getName() <<  " is " << player0->getXOChar() << "." << endl ;
			*currentGameLog << player1->getName() <<  " is " << player1->getXOChar() << "." << endl ;
			*currentGameLog << currentPlayer->getName() << " goes first!" << endl ;
		}
		else if (lastWinner != nullptr) {
			*currentGameLog << "Since " << lastWinner->getName() << " won last, " << currentPlayer->getName() << " goes first!" << endl ;
		}
		else if (lastWinner == nullptr) {
			*currentGameLog << "Since there wasn't a winner last time, the first player will be chosen randomly... " << currentPlayer->getName() << " goes first!" << endl ;
		}
		*currentGameLog << nextPlayer->getName() << " goes second!" << endl << endl <<endl ;
    }
	
	//playerAction(x, y) ; <-uncomment this!
	
	//debug code - delete this
	writeIndex(0, 0, O) ;
	writeIndex(1, 0, X) ;
	writeIndex(2, 0, O) ;
	writeIndex(0, 1, X)	;
	writeIndex(1, 1, O)	;
	writeIndex(2, 1, O) ;
	writeIndex(0, 2, X) ;
	writeIndex(1, 2, X) ;
	writeIndex(2, 2, X) ;
	plyrActnCode = 1 ;
	//end
	
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
		if (winner) {
			*currentGameLog << winPlayer->getName() << " wins! Game over!" << endl << endl ;
		}
		else if(plyrActnCode == 2) {
			*currentGameLog << "Game over! No winners this round." << endl << endl ;
		}
		resetGame() ;
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

void Game::resetGame() {
	if (winner == false) {
		;
	}
	gamesPlayed++ ;
	setStarted(false) ; //will set gameOver state as well
	winner = false ;
	winningXO = nullxo ;
	plyrActnCode = 3 ;
	writeAllIndex(blank) ;
	flushDatabase() ;
	if (winPlayer != nullptr) {
		if (winPlayer == player0) {
			currentPlayer = player0 ;
			nextPlayer = player1 ;
		}
		else if (winPlayer == player1) {
			currentPlayer = player1 ;
			nextPlayer = player0 ;
		}
	}
	else if (winPlayer == nullptr) {
		bool pl0frst = rand() % 2 ;
		if (pl0frst) {
			currentPlayer = player0 ;
			nextPlayer = player1 ;
		}
		else {
			currentPlayer = player1 ;
			nextPlayer = player0 ;
		}
	}
	lastWinner = winPlayer ;
	winPlayer = nullptr ;
}

bool Game::checkLocations() {
	bool ret = false ;
    for (int i = 0 ; i < maxSize ; i++) {
		if (((board[i][0])->getXO()) != blank) {
			if (((board[i][0])->getAllXOType()) != nullptr) {
				Location here = (board[i][0])->getLocation() ;
				XO xo_here = (board[i][0])->getXO() ;
				//<-
				vector<Location> *elsewhere = (board[i][0])->getAllXOType() ;
				ret = findPattern(here, elsewhere, direction::null, 0) ;
				if (ret == true) {
					winningXO = xo_here ;
					return ret ;
				}
			}
		}
    }
	for (int i = 0 ; i < maxSize ; i++) {
		if (((board[0][i])->getXO()) != blank) {
			if (((board[0][i])->getAllXOType()) != nullptr) {
				Location here = (board[0][i])->getLocation() ;
				
				XO xo_here = (board[0][i])->getXO() ;
				vector<Location> *elsewhere = (board[0][i])->getAllXOType() ;
				
				ret = findPattern(here, elsewhere, direction::null, 0) ;
				if (ret == true) {
					winningXO = xo_here ;
					
					return ret ;
				}
			}
		}
    }
	return ret ;
}

bool Game::findPattern(Location here, vector<Location>* elseWhere, direction d, int chainSize) {
	
	//string s = this->toString() ;  //remove this
	
    if (chainSize >= (maxSize-1)) {
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

static int ceiling(int x, int y) {
	if (x > y) {
		return x ;
	}
	else if (y > x) {
		return y ;
	}
	else if(x == y) {
		return ((x+y)/2) ;
	}
	else {
		cout << "how could you possibly screw up something so simple!" << endl ;
		throw new exception() ;
	}
}


