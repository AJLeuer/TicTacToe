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

#ifndef TicTacToe_Game_h
#define TicTacToe_Game_h

using namespace std ;


class Game  {
    
private:
    XO board[3][3] ;
	int boardSize ;
    int rowSize ;
    
    Player *player0 ; //in some cases our player will be human, in others ai
    Player *player1 ;
   
	Player *currentPlayer ; //points to whichever player object has this turn
	Player *nextPlayer ;
	Player *tempPlayer ; //points to a player temporarily
	Player *winPlayer = nullptr ; //obviously null to begin with
	
	int gamesPlayed ;
	int gpCounter ;
    
    std::ostream *currentGameLog ; //record of current game
    
    vector<std::string> *allGamesLog ;
    
    bool player0IsX ;
    
    bool started ; //never assign started directly
	bool winner = false ;
	bool gameOver ; //an extra flag to help functions decide behavior based on game state, differs from completed in that it signifies the time period between the end of one game and the beginning of the next
	
    bool checkStarted() ;
	bool checkSetCompleted() ; //checks to make sure game ended before returning true (completed) or false (not complete)
	void setStarted(bool) ; //always use - never assign started directly
	
	/*Flag to check if writeIndex() and playerAction() are working as intended
	0 if not previously written (write accepted)
	1 if previously written - unwritable index
	2 if all indices written - game over (we can get this more directly from checkComplete())
	If still at 3 then assignement to plyrActnCheck is not working correctly, we will throw an exception */
	int plyrActnCheck = 3 ;
	
	void writeAllIndex(XO) ;
	void resetGame() ; //cleans the game board, resets members, etc.
	
	void checkWin() ;
	bool checkAcross() ;
	bool checkXHlp(int, int/*XO*/) ; //checkAcross helper function
    
public:
    Game() ;
    Game(bool, string) ; //allows for player input on name, X or O
    Game(bool, string, string) ; //also allows player to choose first/second turn
    void initPlayers() ;
    void initPlayers(string, string) ;
    void initPlayers(bool, string, string) ;
    
    char getIndex(int, int) ;
    XO getIndexAsXO(int, int) ;
	bool isWritten(int, int) ;
    
    void writeIndex(int, int, XO) ; //returns 0 if no issues, 1 if unwrittable, 2 if game complete
    void playerAction(int, int) ;
    void nextGameEvent(int, int) ;
    void playSimGame() ;
	void playGameRtime() ;
    
    void wipeGame() ; //resets each space on the board
    
    string toString() ; //returns game state as a string
    string getGameLog() ;
    string getAllLogs() ;
    void printGameState() ;
    
} ;



#endif
