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
	gameCode = 3 ;
	gamesPlayed = 0 ;
	boardSize = sizeof(board)/sizeof(board[0]) ;
    rowSize = sizeof(board[0])/sizeof(board[0][0]) ;
	maxSize = ceiling(boardSize, rowSize) ;
	winningXO = nullxo ;
    setStarted(false) ;
	this->lastWritten = nullptr ;
	initLocVectors() ;
    currentGameLog = new stringstream() ;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0 ; j < rowSize; j++) {
            board[i][j] = new SmartXO(blank, i, j, true) ;
        }
    }
    initPlayers(true, true) ;
}

Game::Game(bool p0Human, bool p1Human, string p0Name) {
	srand((unsigned)time(NULL)) ;
	winner = false ;
	gameCode = 3 ;
	gamesPlayed = 0 ;
	boardSize = sizeof(board)/sizeof(board[0]) ;
    rowSize = sizeof(board[0])/sizeof(board[0][0]) ;
	maxSize = ceiling(boardSize, rowSize) ;
	winningXO = nullxo ;
    setStarted(false) ;
	this->lastWritten = nullptr ;
	initLocVectors() ;
    currentGameLog = new stringstream() ;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0 ; j < rowSize; j++) {
            board[i][j] = new SmartXO(blank, i, j, true) ;
        }
    }
    initPlayers(p0Human, p1Human, p0Name, "Computer") ;
}

Game::Game(bool player0WantsX, bool p0Human, bool p1Human, string p0Name) { //p v ai
    srand((unsigned)time(NULL)) ;
	winner = false ;
	gameCode = 3 ;
	gamesPlayed = 0 ;
	boardSize = sizeof(board)/sizeof(board[0]) ;
    rowSize = sizeof(board[0])/sizeof(board[0][0]) ;
	maxSize = ceiling(boardSize, rowSize) ;
	winningXO = nullxo ;
    setStarted(false) ;
	this->lastWritten = nullptr ;
	initLocVectors() ;
    currentGameLog = new stringstream() ;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0 ; j < rowSize; j++) {
            board[i][j] = new SmartXO(blank, i, j, true) ;
        }
    }
    initPlayers(player0WantsX, p0Human, p1Human, p0Name, "Computer") ;
}

Game::Game(bool player0WantsX, bool p0Human, bool p1Human, string p0Name, string p1Name) { //pvp
    srand((unsigned)time(NULL)) ;
	winner = false ;
	gameCode = 3 ;
	gamesPlayed = 0 ;
	boardSize = sizeof(board)/sizeof(board[0]) ;
    rowSize = sizeof(board[0])/sizeof(board[0][0]) ;
	maxSize = ceiling(boardSize, rowSize) ;
	winningXO = nullxo ;
    setStarted(false) ;
	this->lastWritten = nullptr ;
	initLocVectors() ;
    currentGameLog = new stringstream() ;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0 ; j < rowSize; j++) {
            board[i][j] = new SmartXO(blank, i, j, true) ;
        }
	}
    initPlayers(player0WantsX, p0Human, p1Human, p0Name, p1Name) ;
}

void Game::initPlayers(bool p0Human, bool p1Human) { //auto-inits with preset names
    initPlayers(p0Human, p1Human, "Player0", "Player1") ;
}

void Game::initPlayers(bool p0Human, bool p1Human, string p0Name, string p1Name) {
    bool player0WantsX = rand() % 2 ;
    initPlayers(player0WantsX, p0Human, p1Human, p0Name, p1Name) ;
}

void Game::initPlayers(bool player0WantsX, bool p0Human, bool p1Human, string p0Name, string p1Name) {
    player0 = new Player(p0Name, p0Human) ;
    player1 = new Player(p1Name, p1Human) ;
    
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
	
	//player0->setNextSpace(maxSize+1, maxSize+1) ;
	//player1->setNextSpace(maxSize+1, maxSize+1) ;
}

void Game::initLocVectors() {
	free_locs = nullptr ;
	corner_locs = new vector<Location*>() ;
	corner_locs->push_back(new Location(0, 0)) ;
	corner_locs->push_back(new Location(0, rowSize-1)) ;
	corner_locs->push_back(new Location(boardSize-1, 0)) ;
	corner_locs->push_back(new Location (boardSize-1, rowSize-1)) ;
}

Player* Game::idPlByXO(XO Xo) {
	
	if (player0->getXO() == (Xo)) {
		return player0 ;
	}
	else if(player1->getXO() == (Xo)) {
		return player1 ;
	}
	else {
		cout << "check the idPlByXO() function" << endl ;
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
		manageGame() ;
		if (gameOver) {
			break ;
		}
	}
}

void Game::playGameRtime() {
	currentGameLog = &cout ;
	
	*currentGameLog << "hi" << endl ;
	//todo implement
}

void Game::aiAction() {
	if (corner_locs_free){
		vector<Location*>* free_corners = new vector<Location*>() ;
		bool check = false ;
		for (vector<Location*>::size_type i = 0 ; i < free_locs->size() ; i++) {
			for (vector<Location*>::size_type j = 0 ; j < corner_locs->size() ; j++) {
				if (free_locs->at(i)->equals(corner_locs->at(j))) {
					free_corners->push_back(free_locs->at(i)) ;
					check = true ;
				}
			}
		}
		corner_locs_free = check ;
		if (check) {
			int r = std::rand() % free_corners->size() ;
			vector<Location*>::iterator it = free_corners->begin();
			std::advance(it, r);
			Location *l = it.operator*() ;
			currentPlayer->setNextSpace(l->x, l->y) ;
		}
	}
	else if (!(corner_locs_free)) {
		
	}
	
}


void Game::manageGame() {
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
	
	if (lastWritten == nullptr) {
		free_locs = new vector<Location*>() ;
		for (int i = 0; i < boardSize ; i++) {
			for (int j = 0; j < rowSize; j++) {
				if (!(isWritten(i, j))) {
					Location *l = new Location(i, j) ;
					free_locs->push_back(l) ;
				}
			}
		}
	}
	else {
		for (vector<Location*>::size_type i = 0 ; i < free_locs->size() ; i++) {
			if ((free_locs->at(i))->equals(lastWritten)) {
				free_locs->erase(free_locs->begin() + i) ;
			}
		}
	}
	
	int x ;
	int y ;
	if (currentPlayer->isHuman()) { //we may change this to take console input from a player
		x = rand() % 3 ;
		y = rand() % 3 ;
		currentPlayer->setNextSpace(x, y) ;
	}
	
	else if (!(currentPlayer->isHuman())) {
		
		aiAction() ;
		//this will setNextSpace() also
	}
	
	gameEvent(currentPlayer->getNextSpace()->x, currentPlayer->getNextSpace()->y) ;
	
	checkWin() ;
	
	if ((gameCode == 0) && (!(winner == true))) {
		*currentGameLog << toString() << endl << endl  ;
	}
	else if (gameCode == 1) {
		; //that index was written, we'll try again
	}
	else if (gameCode == 3) {
		cout << "Problem with gameEvent() function. debug" << endl ;
		throw new exception() ;
	}
	if ((gameCode == 2) || (winner == true)) {
		*currentGameLog << toString() << endl << endl  ;
		if (winner) {
			*currentGameLog << winPlayer->getName() << " wins! Game over!" << endl << endl ;
		}
		else if(gameCode == 2) {
			*currentGameLog << "Game over! No winners this round." << endl << endl ;
		}
		resetGame() ;
	}
}

void Game::gameEvent(int x, int y) {
    if (checkSetCompleted()) {
		gameCode = 2 ;
	}
	else if (isWritten(x, y)) {
		gameCode = 1 ;
	}
	else if (!(isWritten(x, y))) {
		writeIndex(x, y, currentPlayer->getXO()) ;
		currentPlayer->setLastWritten(x, y) ;
		delete this->lastWritten ;
		this->lastWritten = new Location(x, y) ;
		tempPlayer = currentPlayer ;
		currentPlayer = nextPlayer ;
		nextPlayer = tempPlayer ;
		if (checkSetCompleted()) {
			gameCode = 2 ; //should end this game
		}
		else {
			gameCode = 0 ;
		}
	}
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
	if (winner == false) {
		;
	}
	gamesPlayed++ ;
	setStarted(false) ; //will set gameOver state as well
	winner = false ;
	winningXO = nullxo ;
	gameCode = 3 ;
	writeAllIndex(blank) ;
	player0->setNextSpace(maxSize+1, maxSize+1) ;
	player1->setNextSpace(maxSize+1, maxSize+1) ;
	player0->setLastWritten() ; //sets to nullptr
	player1->setLastWritten() ;
	this->lastWritten = nullptr ;
	corner_locs_free = true ;
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
				ret = findPattern(here, elsewhere, direction::null, 0, (maxSize-1)) ;
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
				ret = findPattern(here, elsewhere, direction::null, 0, (maxSize-1)) ; //we will search across the array (maxsize - 1)
				if (ret == true) {
					winningXO = xo_here ;
					
					return ret ;
				}
			}
		}
    }
	return ret ;
}

bool Game::findPattern(Location here, vector<Location>* elseWhere, direction d, unsigned lengthSearched, unsigned maxSearch) {
	
    if (lengthSearched >= maxSearch) {
        return true ;
    }
	if ((d == direction::null) || (d == direction::right)) { // then search right next...
		Location *loc = (locSearch(here, elseWhere, 1, 0)) ;
		if (loc != nullptr) {
			return findPattern(*loc, elseWhere, direction::right, (lengthSearched + 1), maxSearch) ;
		}
	}
	if ((d == direction::null) || (d == direction::left)) {
		Location *loc = (locSearch(here, elseWhere, -1, 0)) ;
		if (loc != nullptr) {
			return findPattern(*loc, elseWhere, direction::left, (lengthSearched + 1), maxSearch) ;
		}
	}
	if ((d == direction::null) || (d == direction::up)) {
		Location *loc = (locSearch(here, elseWhere, 0, -1)) ;
		if (loc != nullptr) {
			return findPattern(*loc, elseWhere, direction::up, (lengthSearched + 1), maxSearch) ;
		}
	}
	if ((d == direction::null) || (d == direction::down)) {
		Location *loc = (locSearch(here, elseWhere, 0, 1)) ;
		if (loc != nullptr) {
			return findPattern(*loc, elseWhere, direction::down, (lengthSearched + 1), maxSearch) ;
		}
	}
	if ((d == direction::null) || (d == direction::upRight)) {
		Location *loc = (locSearch(here, elseWhere, 1, -1)) ;
		if (loc != nullptr) {
			return findPattern(*loc, elseWhere, direction::upRight, (lengthSearched + 1), maxSearch) ;
		}
	}
	if ((d == direction::null) || (d == direction::upLeft)) {
		Location *loc = (locSearch(here, elseWhere, -1, -1)) ;
		if (loc != nullptr) {
			return findPattern(*loc, elseWhere, direction::upLeft, (lengthSearched + 1), maxSearch) ;
		}
	}
	if ((d == direction::null) || (d == direction::downRight)) {
		Location *loc = (locSearch(here, elseWhere, 1, 1)) ;
		if (loc != nullptr) {
			return findPattern(*loc, elseWhere, direction::downRight, (lengthSearched + 1), maxSearch) ;
		}
	}
	if ((d == direction::null) || (d == direction::downLeft)) {
		Location *loc = (locSearch(here, elseWhere, -1, 1)) ;
		if (loc != nullptr) {
			return findPattern(*loc, elseWhere, direction::downLeft, (lengthSearched + 1), maxSearch) ;
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
    for (int i = 0; i < rowSize ; i++) {
        for (int j = 0 ; j < boardSize ; j++) {
            if (j == 0) {
				*gameString << getIndex(j, i) ;
			}
            if ((j > 0) && (j < (boardSize - 1))) {
                if (getIndex(j, i) == ' ') {
					*gameString << " |" << getIndex(j, i) << " |" ;
				}
                else {
					*gameString << " | " << getIndex(j, i) << "|" ;
				}
            }
            if (j == (boardSize - 1)) {
				*gameString << getIndex(j, i) << endl ;
			}
        }
        if (i < (rowSize - 1)) {
            *gameString << "-- -- --" ;
            *gameString << endl ;
        }
        if (i == (rowSize - 1)) {
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


static unsigned ceiling(unsigned x, unsigned y) {
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
		cout << "problem with ceiling func" << endl ;
		throw new exception() ;
	}
}


