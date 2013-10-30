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
#include "stdafx.h"

using namespace std ;

Game::Game() { //best for ai v ai
    srand((unsigned)time(NULL)) ;
	winner = false ;
	plyrActnCheck = 3 ;
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
	plyrActnCheck = 3 ;
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
	plyrActnCheck = 3 ;
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
            if (!(isWritten(i, j)))
			allWritten = false ;
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
    if (((((board[x][y]))->getXO()) == X) || ((((board[x][y]))->getXO()) == O))
	return true ;
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
	setStarted(false) ;
	winner = false ;
	gameOver = true ; //setting = true means resetting in this case
	plyrActnCheck = 3 ;
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
    if (checkSetCompleted())
	plyrActnCheck = 2 ;
	else if (isWritten(x, y))
	plyrActnCheck = 1 ;
	else if (!(isWritten(x, y))){
		writeIndex(x, y, currentPlayer->getXO()) ;
		tempPlayer = currentPlayer ;
		currentPlayer = nextPlayer ;
		nextPlayer = tempPlayer ;
		if (checkSetCompleted())
		plyrActnCheck = 2 ; //should end this game
		else
		plyrActnCheck = 0 ;
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
		else
		*currentGameLog << "Since " << currentPlayer->name << " won last, " << currentPlayer->name << " goes first!" << endl ;
		*currentGameLog << nextPlayer->name << " goes second!" << endl << endl <<endl ;
    }
	playerAction(x, y) ;
	
	
	checkWin() ;
	
	if ((plyrActnCheck == 0) && (!(winner == true)))
	*currentGameLog << toString() << endl << endl  ;
	else if (plyrActnCheck== 1)
	;
	else if (plyrActnCheck == 3) {
		cout << "Problem with playerAction() function. Adam can debug" << endl ;
		throw new exception() ;
	}
	if ((plyrActnCheck == 2) || (winner == true)) {
		*currentGameLog << toString() << endl << endl  ;
		
		*currentGameLog << winPlayer->name << " wins! Game over!" << endl << endl ;
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
	//code
}

string Game::toString() {
    stringstream *gameString = new stringstream() ;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0 ; j < rowSize; j++) {
            if (j == 0)
			*gameString << getIndex(j,i) ;
            if ((j > 0) && (j < (rowSize - 1))) {
                if (getIndex(i, j) == ' ')
				*gameString << " |" << getIndex(j,i) << " |" ;
                else
				*gameString << " | " << getIndex(j,i) << "|" ;
            }
            if (j == (rowSize - 1))
			*gameString << getIndex(j, i) << endl ;
        }
        if (i < (boardSize - 1)) {
            *gameString << "-- -- --" ;
            *gameString << endl ;
        }
        if (i == (boardSize - 1))
		*gameString << endl ;
    }
    return gameString->str() ;
}

string Game::getGameLog() {
	stringstream *tempLog = new stringstream() ;
	*tempLog << currentGameLog->rdbuf() ;
    return tempLog->str() ;
}

void Game::checkWin() {
	bool won = checkAcross() ;
	
	winPlayer = player0 ;
	winner = won ;
	
	
}

bool Game::checkLocations() {
	for (int i = 0 ; i < boardSize ; i++) {
		for (int j = 0 ; j < rowSize ; j++ ) {
			if (((board[i][j])->getSTypeL()) != nullptr) {
				Location here = board[i][j]->getLocation() ;
				vector<Location> *elsewhere = board[i][j]->getSTypeL() ;
				findPattern(here, elsewhere, direction::right, i, j, 0) ;
				cout << (board[i][j])->getSTypeL()->back().x << endl ;
			}
		}
	}
	return false ;
}

bool Game::findPattern(Location here, vector<Location>* elseWhere, direction d, int x, int y, int i) {
	if (i < elseWhere->size()) {
		if(((elseWhere->at(i).x) == (here.x + 1)) && ((elseWhere->at(i).y) == (here.y)))
		
		
	}
	
}




