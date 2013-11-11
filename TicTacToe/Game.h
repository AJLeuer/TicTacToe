//
//  Game.h
//  TicTacToe
//
//  Created by Adam James Leuer on 10/23/13.
//  Copyright (c) 2013 Adam James Leuer. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <vector>

#include "Player.h"
#include "XO.h"
#include "SmartXO.h"
#include "Location.h"

#ifndef TicTacToe_Game_h
#define TicTacToe_Game_h

using namespace std ;

enum direction {
    null,
	up,
	down,
	right,
	left,
	upRight,
	upLeft,
	downRight,
	downLeft
} ;

class Game : public SmartXO {
    
protected:
    SmartXO* board[(unsigned)3][(unsigned)3] ;
	
	 //the larger of the rows or columns (in case they were ever different)
	unsigned boardSize ;
    unsigned rowSize ;
	unsigned maxSize ;
	
    
    Player *player0 ; //in some cases our player will be human, in others ai
    Player *player1 ;
	
	Player *currentPlayer ; //points to whichever player object has this turn
	Player *nextPlayer ;
	Player *tempPlayer ; //points to a player temporarily
	Player *winPlayer ; //obviously null to begin with
	Player *lastWinner ;
	XO winningXO ; //the X or O used by the winning player
	Location *lastWritten ;
	
	Player thisPlayer() ;
	Player otherPlayer() ;
	
	vector<Location*>* free_locs ;
	vector<Location*>* corner_locs ;
	bool corner_locs_free = true ; //there are still corners that haven't been written
	
	void initLocVectors() ;
	
	
	int gamesPlayed ;
    
    std::ostream *currentGameLog ; //record of current game
    
    vector<std::string> *allGamesLog ;
    
    bool player0IsX ;
    
    bool started ; //never assign started directly
	bool winner ;
	bool gameOver ; //an extra flag to help functions decide behavior based on game state, differs from completed in that it signifies the time period between the end of one game and the beginning of the next
	
    bool checkStarted() ;
	bool checkSetCompleted() ; //checks to make sure game ended before returning true (completed) or false (not complete)
	void setStarted(bool) ; //always use - never assign started directly
	
	/*Flag to check if writeIndex() and playerAction() are working as intended
	 0 if not previously written (write accepted)
	 1 if previously written - unwritable index
	 2 if all indices written - game over (we can get this more directly from checkComplete())
	 If still at 3 then assignment to gameCode is not working correctly, we will throw an exception */
	int gameCode ;
	
	void writeAllIndex(XO) ;
	void resetGame() ; //cleans the game board, resets members, etc.
	
	void checkWin() ;
	bool checkLocations() ;
	bool findPattern(Location, vector<Location>*, direction, unsigned lengthSearched, unsigned maxSearch) ; //takes a direction in which to recursively search for a straight line of Xs or Os. unsigned lengthSearched keeps track of how far we've searched, unsigned maxSearch sets the limit on the length of our search
	Location* locSearch(Location, vector<Location>*, int, int) ; //searches through vector of locations to find any that are 1 unit away
	
	void aiAction() ; //AI function to choose the next spot to place X or O

public:
    Game() ;
	Game(bool, bool, string) ;
    Game(bool, bool, bool, string) ; //allows for player input on name, X or O
    Game(bool, bool, bool, string, string) ; //also allows player to choose first/second turn
    void initPlayers(bool, bool) ;
    void initPlayers(bool, bool, string, string) ;
    void initPlayers(bool, bool, bool, string, string) ;
	
	Player* idPlByXO(XO) ; //identifies player by their X or O
    
    char getIndex(int, int) ;
    XO getIndexAsXO(int, int) ;
	bool isWritten(int, int) ;
	
	
    
    void writeIndex(int, int, XO) ; //returns 0 if no issues, 1 if unwrittable, 2 if game complete
    void gameEvent(int, int) ;
    void manageGame() ;
	
	//These functions (or the one below, or any other similar one) is responsible for controlling whether the currentPlayer behaves as an true AI, a simple random # generator, or takes input from a human
    void playSimGame() ; //plays as a simulated human that randomly generates choices (not true AI) - pitted against a true AI player. One player must be specified as human in the constructor, the other as non-human (false)
	void playGameRtime() ;
	
    
    void wipeGame() ; //resets each space on the board
    
    std::string toString() ; //returns game state as a string
    std::string getGameLog() ;
    std::string getAllLogs() ;
    void printGameState() ;
	
} ;

static unsigned ceiling(unsigned, unsigned) ;

void pause(int seconds) ;



#endif
