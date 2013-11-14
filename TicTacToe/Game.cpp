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
	initVectors() ;
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
	initVectors() ;
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
	initVectors() ;
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
	initVectors() ;
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
	//todo implement
}

void Game::aiAction() {
	
	bool decisionMade = false ;
	XO myxo = currentPlayer->getXO() ;
	vector<Location>* thisPlSpots = SmartXO::getAllLoc(myxo) ;
	XO oppxo = nextPlayer->getXO() ;
	vector<Location>* oppPlSpots = SmartXO::getAllLoc(oppxo) ;
	
	if ((oppPlSpots != nullptr) && (decisionMade == false)) { //if the opposing player has 2 in a row we will set our next space to be the end of that sequence
		
		Navigator *nav = new Navigator() ;
		Navigator *searched = nullptr ;
		for (vector<SmartXO*>::size_type i = 0 ; i < oppPlSpots->size() ; i++) {
			nav->b = false ; nav->dir = direction::null ; nav->loc = nullptr ; nav->lengthSearched = 0 ;
			searched = findSequence(oppPlSpots->at(i), nav, oppPlSpots, 1, 1) ;
			if (searched->b == true) {
				Location *loc1 = findIndex(searched->loc, searched->dir, 1) ;
				Location *loc2 = findIndex(searched->loc, reverse(searched->dir), (searched->lengthSearched +1)) ;
				if (loc1 != nullptr) {
					currentPlayer->setNextSpace(loc1->x, loc1->y) ;
					decisionMade = true ;
					break ;
				}
				else if (loc2 != nullptr) {
					currentPlayer->setNextSpace(loc2->x, loc2->y) ;
					decisionMade = true ;
					break ;
				}
			}
		}
	}
	if ((oppPlSpots != nullptr) && (decisionMade == false)) { //if the opposing player has X or Os on opposite sides of the boards, we will set out next write to be in between
		Navigator *nav = new Navigator() ;
		Navigator *searched = nullptr ;
		nav->b = false ; nav->dir = direction::null ; nav->loc = nullptr ; nav->lengthSearched = 0 ;
		for (vector<SmartXO*>::size_type i = 0 ; i < oppPlSpots->size() ; i++) {
			Location l = (oppPlSpots->at(i)) ;
			if (((l.x == 0) || (l.x == (boardSize-1))) || ((l.y == 0) || (l.y == (rowSize-1)))) {
				searched = findSequence(l, nav, oppPlSpots, (maxSize-1), (maxSize-1)) ;
				if (searched->b == true) {
					Location* locn = findIndex(searched->loc, reverse(searched->dir), 1) ;
					if (locn != nullptr) {
						currentPlayer->setNextSpace(locn->x, locn->y) ;
						decisionMade = true ;
						break ;
					}
				}
			}
		}
	}
	
	if ((thisPlSpots != nullptr) && (decisionMade == false)) { //if we have two in a row already this behavior fills in the last space
		Navigator *nav = new Navigator() ;
		Navigator *searched = nullptr ;
		nav->b = false ; nav->dir = direction::null ; nav->loc = nullptr ; nav->lengthSearched = 0 ;
		for (vector<SmartXO*>::size_type i = 0 ; i < thisPlSpots->size() ; i++) {
			searched = findSequence(thisPlSpots->at(i), nav, thisPlSpots, 1, 1) ; // we will search for a line of at any two of our X or Os in a row (arg 1 here really means 2 in a row - start at 0, add 1 if we find a second in line with it)
			if (searched->b == true) {
				Location *locn = findIndex(searched->loc, searched->dir, 1) ;
				if (locn != nullptr) {
					currentPlayer->setNextSpace(locn->x, locn->y) ;
					decisionMade = true ;
					break ;
				}
			}
		}
	}
	if ((thisPlSpots != nullptr) && (decisionMade == false)) { //this behavior searches to find a location in between currentPlayer's X or O, and sets it to be written
		Navigator *nav = new Navigator() ;
		Navigator *searched = nullptr ;
		nav->b = false ; nav->dir = direction::null ; nav->loc = nullptr ; nav->lengthSearched = 0 ;
		for (vector<SmartXO*>::size_type i = 0 ; i < thisPlSpots->size() ; i++) {
			Location l = (thisPlSpots->at(i)) ;
			if (((l.x == 0) || (l.x == (boardSize-1))) || ((l.y == 0) || (l.y == (rowSize-1)))) {
				searched = findSequence(l, nav, thisPlSpots, (maxSize-1), (maxSize-1)) ;
				if (searched->b == true) {
					Location* locn = findIndex(searched->loc, reverse(searched->dir), 1) ;
					if (locn != nullptr) {
						currentPlayer->setNextSpace(locn->x, locn->y) ;
						decisionMade = true ;
						break ;
					}
				}
			}
		}
	}
	if ((cornersFree()) && (decisionMade == false)) {
		while (decisionMade == false) {
			int r = std::rand() % freeCorners->size() ;
			vector<Location*>::iterator it = freeCorners->begin();
			std::advance(it, r);
			Location *l = it.operator*() ;
			if (!(isWritten(l->x, l->y))) {
				decisionMade = true ;
				currentPlayer->setNextSpace(l->x, l->y) ;
			}
		}
	}
	if ((!(cornersFree())) && (decisionMade == false)) {
		unsigned center = (boardSize/2) ;
		unsigned middle = (rowSize/2) ;
		if (!(isWritten(center, middle))) {
			decisionMade = true ;
			currentPlayer->setNextSpace(center, middle) ;
		}
		
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
	
	updateFreeLocations() ;
	
	/*this block, up to gameEvent(), will handle all possible combinations of player opponents. Human vs human, human vs ai, ai vs ai, etc. Since gameEvent() switches the *currentPlayer pointer each time, we don't have to worry about specifying which player we're working with
	 */
	if (currentPlayer->isHuman()) { //we may change this to take console input from a player
		
		if (currentPlayer->getTurns() == 0) {
			currentPlayer->setNextSpace(1, 1) ;
		}
		else if (currentPlayer->getTurns() == 1) {
			currentPlayer->setNextSpace(2, 1) ;
		}
		else if (currentPlayer->getTurns() == 2) {
			currentPlayer->setNextSpace(1, 2) ;
		}
		else {
			int x = rand() % 3 ;
			int y = rand() % 3 ;
			currentPlayer->setNextSpace(x, y) ;
		}
	}
	else if (!(currentPlayer->isHuman())) {
		aiAction() ;
		//this will setNextSpace() also
	}
	
	gameEvent() ;
	
	checkWin() ;
	
	if ((gameCode == 0) && (!(winner == true))) { //this loop placed a new XO on the board, so we'll go to the next turn
		*currentGameLog << toString() << endl << endl  ;
	}
	else if (gameCode == 1) { //that index was written, we'll try again
		;
	}
	else if (gameCode == 3) {
		cout << "Problem with gameEvent() function. debug" << endl ;
		throw new exception() ;
	}
	if ((gameCode == 2) || (winner == true)) { //then we've reached end of game
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

void Game::gameEvent() {
	Location *p = currentPlayer->getNextSpace() ;
    if (checkSetCompleted()) {
		gameCode = 2 ;
	}
	else if (isWritten(p->x, p->y)) {
		gameCode = 1 ;
	}
	else if (!(isWritten(p->x, p->y))) {
		writeIndex(p->x, p->y, currentPlayer->getXO()) ;
		currentPlayer->incTurns() ;
		currentPlayer->setLastWritten(p->x, p->y) ;
		delete this->lastWritten ;
		this->lastWritten = new Location(p->x, p->y) ;
		tempPlayer = currentPlayer ;
		currentPlayer = nextPlayer ;
		nextPlayer = tempPlayer ;
		gameCode = 0 ;
	}
	if (checkSetCompleted()) {
		gameCode = 2 ; //should end this game
	}
}



void Game::writeIndex(int x, int y, XO inp) {
    *(board[x][y]) = inp ;
}

Location* Game::findIndex(Location* loc, direction dir, int offset) {
	if (dir == direction::right) {
		if (((loc->x + offset) < boardSize) && (!(isWritten((loc->x + offset), loc->y)))) {
			Location* rloc = new Location((loc->x + offset), loc->y) ;
			return rloc ;
		}
		else {
			return nullptr ;
		}
	}
	else if (dir == direction::left) {
		if (((loc->x - offset) >= 0) && (!(isWritten((loc->x - offset), loc->y)))) {
			Location* rloc = new Location((loc->x - offset), loc->y) ;
			return rloc ;
		}
		else {
			return nullptr ;
		}
	}
	else if (dir == direction::up) {
		if (((loc->y - offset) >= 0) && (!(isWritten(loc->x, (loc->y - offset))))) {
			Location* rloc = new Location(loc->x, (loc->y - offset)) ;
			return rloc ;
		}
		else {
			return nullptr ;
		}
	}
	else if (dir == direction::down) {
		if (((loc->y + offset) < rowSize) && (!(isWritten(loc->x, (loc->y + offset))))) {
			Location* rloc = new Location(loc->x, (loc->y + offset)) ;
			return rloc ;
		}
		else {
			return nullptr ;
		}
	}
	else if (dir == direction::upRight) {
		if ((((loc->x + offset) < boardSize) && ((loc->y - offset) >= 0)) && (!(isWritten((loc->x + offset), (loc->y - offset))))) {
			Location* rloc = new Location((loc->x + offset), (loc->y - offset)) ;
			return rloc ;
		}
		else {
			return nullptr ;
		}
	}
	else if (dir == direction::upLeft) {
		if ((((loc->x - offset) >= 0) && ((loc->y - offset) >= 0)) && (!(isWritten((loc->x - offset), (loc->y - offset))))) {
			Location* rloc = new Location((loc->x - offset), (loc->y - offset)) ;
			return rloc ;
		}
		else {
			return nullptr ;
		}
	}
	else if (dir == direction::downRight) {
		if ((((loc->x + offset) < boardSize) && ((loc->y + offset) < rowSize)) && (!(isWritten((loc->x + offset), (loc->y + offset))))) {
			Location* rloc = new Location((loc->x + offset), (loc->y + offset)) ;
			return rloc ;
		}
		else {
			return nullptr ;
		}
	}
	else if (dir == direction::downLeft) {
		if ((((loc->x - offset) >= 0) && ((loc->y + offset) < rowSize)) && (!(isWritten((loc->x - offset), (loc->y + offset))))) {
			Location* rloc = new Location((loc->x - offset), (loc->y + offset)) ;
			return rloc ;
		}
		else {
			return nullptr ;
		}
	}
	else {
		cout << "Problem with writeIndex(Location...)" << endl ;
		throw new exception() ;
	}
}

direction Game::reverse(direction dir) {
	if (dir == direction::right) {
		return direction::left ;
	}
	else if (dir == direction::left) {
		return direction::right ;
	}
	else if (dir == direction::up) {
		return direction::down ;
	}
	else if (dir == direction::down) {
		return direction::up ;
	}
	else if (dir == direction::upRight) {
		return direction::downLeft ;
	}
	else if (dir == direction::upLeft) {
		return direction::downRight ;
	}
	else if (dir == direction::downRight) {
		return direction::upLeft ;
	}
	else /*if (dir == direction::downLeft) */ {
		return direction::upRight ;
	}
}

bool Game::openSequence(vector<Location>* thisPlSpots, vector<Location>* oppPlSpots, Location check) {
	return false ;
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
	player0->resetTurns() ;
	player1->resetTurns() ;
	player0->setNextSpace(maxSize+1, maxSize+1) ;
	player1->setNextSpace(maxSize+1, maxSize+1) ;
	player0->setLastWritten() ; //sets to nullptr
	player1->setLastWritten() ;
	this->lastWritten = nullptr ;
	destrVectors() ;
	initVectors() ;
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
			XO xo = (board[i][0])->getXO() ;
			if ((SmartXO::getAllLoc(xo)) != nullptr) {
				Location here = (board[i][0])->getLocation() ;
				vector<Location> *elsewhere = SmartXO::getAllLoc(xo) ;
				Navigator *nav = new Navigator() ;
				nav->b = false ; nav->dir = direction::null ; nav->loc = nullptr ; nav->lengthSearched = 0 ;
				Navigator *searched = findSequence(here, nav, elsewhere, 1, (maxSize-1)) ;
				ret = searched->b ; //we will search across the array (maxsize - 1)
				if (ret == true) {
					winningXO = xo ;
					return ret ;
				}
			}
		}
    }
	for (int i = 0 ; i < maxSize ; i++) {
		if (((board[0][i])->getXO()) != blank) {
			XO xo = (board[0][i])->getXO() ;
			if ((SmartXO::getAllLoc(xo)) != nullptr) {
				Location here = (board[0][i])->getLocation() ;
				XO xo_here = (board[0][i])->getXO() ;
				vector<Location> *elsewhere = SmartXO::getAllLoc(xo) ;
				Navigator *nav = new Navigator() ;
				nav->b = false ; nav->dir = direction::null ; nav->loc = nullptr ; nav->lengthSearched = 0 ;
				Navigator *searched = findSequence(here, nav, elsewhere, 1, (maxSize-1)) ;
				ret = searched->b ; //we will search across the array (maxsize - 1)
				if (ret == true) {
					winningXO = xo_here ;
					return ret ;
				}
			}
		}
    }
	return ret ;
}

Navigator* Game::findSequence(Location here, Navigator* nav, vector<Location>* elseWhere, int offset, unsigned maxSearch) {
	
    if (nav->lengthSearched >= maxSearch) {
		nav->b = true ;
        return nav ;
    }
	if ((nav->dir == direction::null) || (nav->dir == direction::right)) { // then search right next...
		Location *nearby = (locSearch(here, elseWhere, offset, 0)) ;
		if (nearby != nullptr) {
			nav->lengthSearched = (nav->lengthSearched + offset) ;
			nav->loc = nearby ;
			nav->dir = direction::right ;
			return findSequence(*nearby, nav, elseWhere, offset, maxSearch) ;
		}
	}
	if ((nav->dir == direction::null) || (nav->dir == direction::left)) {
		Location *nearby = (locSearch(here, elseWhere, -offset, 0)) ;
		if (nearby != nullptr) {
			nav->lengthSearched = (nav->lengthSearched + offset) ;
			nav->loc = nearby ;
			nav->dir = direction::left ;
			return findSequence(*nearby, nav, elseWhere, offset, maxSearch) ;
		}
	}
	if ((nav->dir == direction::null) || (nav->dir == direction::up)) {
		Location *nearby = (locSearch(here, elseWhere, 0, -offset)) ;
		if (nearby != nullptr) {
			nav->lengthSearched = (nav->lengthSearched + offset) ;
			nav->loc = nearby ;
			nav->dir = direction::up ;
			return findSequence(*nearby, nav, elseWhere, offset, maxSearch) ;
		}
	}
	if ((nav->dir == direction::null) || (nav->dir == direction::down)) {
		Location *nearby = (locSearch(here, elseWhere, 0, offset)) ;
		if (nearby != nullptr) {
			nav->lengthSearched = (nav->lengthSearched + offset) ;
			nav->loc = nearby ;
			nav->dir = direction::down ;
			return findSequence(*nearby, nav, elseWhere, offset, maxSearch) ;
		}
	}
	if ((nav->dir == direction::null) || (nav->dir == direction::upRight)) {
		Location *nearby = (locSearch(here, elseWhere, offset, -offset)) ;
		if (nearby != nullptr) {
			nav->lengthSearched = (nav->lengthSearched + offset) ;
			nav->loc = nearby ;
			nav->dir = direction::upRight ;
			return findSequence(*nearby, nav, elseWhere, offset, maxSearch) ;
		}
	}
	if ((nav->dir == direction::null) || (nav->dir == direction::upLeft)) {
		Location *nearby = (locSearch(here, elseWhere, -offset, -offset)) ;
		if (nearby != nullptr) {
			nav->lengthSearched = (nav->lengthSearched + offset) ;
			nav->loc = nearby ;
			nav->dir = direction::upLeft ;
			return findSequence(*nearby, nav, elseWhere, offset, maxSearch) ;
		}
	}
	if ((nav->dir == direction::null) || (nav->dir == direction::downRight)) {
		Location *nearby = (locSearch(here, elseWhere, offset, offset)) ;
		if (nearby != nullptr) {
			nav->lengthSearched = (nav->lengthSearched + offset) ;
			nav->loc = nearby ;
			nav->dir = direction::downRight ;
			return findSequence(*nearby, nav, elseWhere, offset, maxSearch) ;
		}
	}
	if ((nav->dir == direction::null) || (nav->dir == direction::downLeft)) {
		Location *nearby = (locSearch(here, elseWhere, -offset, offset)) ;
		if (nearby != nullptr) {
			nav->lengthSearched = (nav->lengthSearched + offset) ;
			nav->loc = nearby ;
			nav->dir = direction::downLeft ;
			return findSequence(*nearby, nav, elseWhere, offset, maxSearch) ;
		}
	}
	nav->b = false ;
	return nav ;
	
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

void Game::initVectors() {
	freeLocations = nullptr ;
	freeCorners = nullptr ;
	corners = new vector<Location*>() ;
	corners->push_back(new Location(0, 0)) ;
	corners->push_back(new Location(0, rowSize-1)) ;
	corners->push_back(new Location(boardSize-1, 0)) ;
	corners->push_back(new Location (boardSize-1, rowSize-1)) ;
}

void Game::destrVectors() {
	delete freeLocations ;
	delete freeCorners ;
	delete corners ;
}

void Game::updateFreeLocations() { //updates freeCorners as well
	if (freeLocations == nullptr) {
		freeLocations = new vector<Location*>() ;
		for (int i = 0; i < boardSize ; i++) {
			for (int j = 0; j < rowSize; j++) {
				if (!(isWritten(i, j))) {
					Location *l = new Location(i, j) ;
					freeLocations->push_back(l) ;
				}
			}
		}
	}
	if (freeCorners == nullptr) {
		freeCorners = new vector<Location*>() ;
		for (vector<Location*>::size_type i = 0 ; i < freeLocations->size() ; i++) {
			for (vector<Location*>::size_type j = 0 ; j < corners->size() ; j++) {
				if (freeLocations->at(i)->equals(corners->at(j))) {
					freeCorners->push_back(freeLocations->at(i)) ;
				}
			}
		}
	}
	if (lastWritten != nullptr) {
		for (vector<Location*>::size_type i = 0 ; i < freeLocations->size() ; i++) {
			if ((freeLocations->at(i))->equals(lastWritten)) {
				freeLocations->erase(freeLocations->begin() + i) ;
			}
			if (i < freeCorners->size()) {
				if ((freeCorners->at(i))->equals(lastWritten)) {
					freeCorners->erase(freeCorners->begin() + i) ;
				}
			}
		}
	}
}

bool Game::cornersFree() {
	return (freeCorners->size() > 0) ;
}


static int ceiling(int x, int y) {
	if (x > y) {
		return x ;
	}
	else if (y > x) {
		return y ;
	}
	else {
		return ((x+y)/2) ;
	}
}

static int floor(int x, int y) {
	if (y < x) {
		return y ;
	}
	return x ;
}


