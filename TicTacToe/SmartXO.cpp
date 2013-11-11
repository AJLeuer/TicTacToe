#include <iterator>
#include <iostream>
#include <sstream>


#include "SmartXO.h"
#include "Game.h"
#include "Location.h"


using namespace std ;

unsigned int iDs = 0 ;

Location::Location() {
	x = 0 ;
	y = 0 ;
}

vector<SmartXO*>* xDatabase = new vector<SmartXO*>() ;
vector<SmartXO*>* oDatabase = new vector<SmartXO*>() ;

SmartXO::SmartXO() { //this object won't be placed on the game board
	this->id = iDs + 500 ;
	iDs++ ;
	this->xo = blank ;
	this->location.x = -500 ;
	this->location.y = -500 ;
	this->on_board = false ;
}

SmartXO::SmartXO(XO xorO, int xloc, int yloc, bool ob) {
	this->id = iDs ;
	iDs++ ;
	(this->xo) = xorO ;
	this->location.x = xloc ;
	this->location.y = yloc ;
	this->on_board = ob ;
	if(this->on_board == true) {
		if(this->getXO() == X) {
			xDatabase->push_back(this) ;
		}
		else if(this->getXO() == O) {
			oDatabase->push_back(this) ;
		}
	}
}

void SmartXO::flushDatabase() {
	delete xDatabase ;
	delete oDatabase ;
	
	xDatabase = new vector<SmartXO*>() ;
	oDatabase = new vector<SmartXO*>() ;
}



void SmartXO::operator=(XO xorO) {
	/*
	if (((xorO == X) || (xorO == O)) && ((this->getXO() == X) || (this->getXO() == O))) {
		std::cout << "A previously written smartXO may only be overwritten with blank." << std::endl ;
		throw new exception() ;
	}
	*/
	
	//it's safe to assign the XO member:
	(this->xo) = xorO ;
	
	//check to make sure this smartXO isn't in a database already:
	vector<SmartXO*>::size_type x = xDatabase->size() ;
	vector<SmartXO*>::size_type o = oDatabase->size() ;
	for (vector<SmartXO*>::size_type i = 0; ((i < x) || (i < o)) ; i++) {
		if(i < x) {
			if ((xDatabase->at(i)->getID()) == (this->getID())) {
				xDatabase->erase((xDatabase->begin()) + i) ;
				x = xDatabase->size() ;
			}
		}
		if (i < o) {
			if ((oDatabase->at(i)->getID()) == (this->getID())) {
				oDatabase->erase((oDatabase->begin()) + i) ;
				o = oDatabase->size() ;
			}
		}
	}
	//then add this smartXO to its database:
	if (this->on_board) {
		if(this->getXO() == X) {
			xDatabase->push_back(this) ;
		}
		else if(this->getXO() == O) {
			oDatabase->push_back(this) ;
		}
	}
}

bool SmartXO::compXO(XO first, XO second) {
	if ((first == blank) || (second == blank)) {
		return false ;
	}
	else if ((first == X) && (second == X)) {
		return true ;
	}
	else if ((first == O) && (second == O)) {
		return true ;
	}
	return false ;
	
}

Location SmartXO::getLocation() {
	return this->location ;
}

int SmartXO::getID() {
	return this->id ;
}

XO SmartXO::getXO() {
	
	return xo ;
}

char SmartXO::getXOChar(XO xO) {
	SmartXO* Xo = new SmartXO(xO, -499, -499, false) ;
	return (char)(Xo->getXO()) ;
}

vector<Location>* SmartXO::getAllXOType() {
	XO txo = this->getXO() ;
	if (txo == X) {
		vector<Location>* xlocs = new vector<Location> ;
		for(vector<SmartXO*>::size_type i = 0 ; i < xDatabase->size() ; i++) {
			Location dbLoc = (xDatabase->at(i))->getLocation() ;
			xlocs->push_back(dbLoc) ;
		}
		return xlocs ;
	}
	else if (txo == O) {
		vector<Location>* olocs = new vector<Location> ;
		for(vector<SmartXO*>::size_type i = 0 ; i < oDatabase->size() ; i++) {
			Location dbLoc = (oDatabase->at(i))->getLocation() ;
			olocs->push_back(dbLoc) ;
		}
		return olocs ;
	}
	return nullptr ;
}