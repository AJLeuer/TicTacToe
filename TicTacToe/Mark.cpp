#include <iterator>
#include <iostream>
#include <sstream>


#include "Mark.h"
#include "Game.h"
#include "Location.h"


using namespace std ;

unsigned int iDs = 0 ;

Location::Location() {
	x = 0 ;
	y = 0 ;
}


vector<Mark*>* xDatabase = new vector<Mark*>() ;
vector<Mark*>* oDatabase = new vector<Mark*>() ;

Mark::Mark() { //this object won't be placed on the game board
	this->id = iDs + 500 ;
	iDs++ ;
	this->type = blank ;
	this->location.x = -500 ;
	this->location.y = -500 ;
	this->on_board = false ;
}

Mark::Mark(Type type, int xloc, int yloc, bool ob) {
	this->id = iDs ;
	iDs++ ;
	(this->type) = type ;
	this->location.x = xloc ;
	this->location.y = yloc ;
	this->on_board = ob ;
	if(this->on_board == true) {
		if(this->getType() == X) {
			xDatabase->push_back(this) ;
		}
		else if(this->getType() == O) {
			oDatabase->push_back(this) ;
		}
	}
}

void Mark::flushDatabase() {
	delete xDatabase ;
	delete oDatabase ;
	
	xDatabase = new vector<Mark*>() ;
	oDatabase = new vector<Mark*>() ;
}



void Mark::operator=(Type type) {
	/*
	if (((xorO == X) || (xorO == O)) && ((this->getXO() == X) || (this->getXO() == O))) {
		std::cout << "A previously written smartXO may only be overwritten with blank." << std::endl ;
		throw new exception() ;
	}
	*/
	
	//it's safe to assign the XO member:
	(this->type) = type ;
	
	//check to make sure this smartXO isn't in a database already:
	vector<Mark*>::size_type x = xDatabase->size() ;
	vector<Mark*>::size_type o = oDatabase->size() ;
	for (vector<Mark*>::size_type i = 0; ((i < x) || (i < o)) ; i++) {
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
		if(this->getType() == X) {
			xDatabase->push_back(this) ;
		}
		else if(this->getType() == O) {
			oDatabase->push_back(this) ;
		}
	}
}

bool Mark::compareTypes(Type first, Type second) {
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

Location Mark::getLocation() {
	return this->location ;
}

int Mark::getID() {
	return this->id ;
}

Type Mark::getType() {
	return type ;
}

char Mark::getMarkType(Type type) {
	Mark* Xo = new Mark(type, -499, -499, false) ;
	return (char)(Xo->getType()) ;
}

vector<Location>* Mark::getAllLocations(Type type) {
	if ((xDatabase->size() > 0) && (type == X)) {
		vector<Location>* xlocs = new vector<Location> ;
		for(vector<Mark*>::size_type i = 0 ; i < xDatabase->size() ; i++) {
			Location dbLoc = (xDatabase->at(i))->getLocation() ;
			xlocs->push_back(dbLoc) ;
		}
		return xlocs ;
	}
	else if ((oDatabase->size() > 0) && (type == O)) {
		vector<Location>* olocs = new vector<Location> ;
		for(vector<Mark*>::size_type i = 0 ; i < oDatabase->size() ; i++) {
			Location dbLoc = (oDatabase->at(i))->getLocation() ;
			olocs->push_back(dbLoc) ;
		}
		return olocs ;
	}
	return nullptr ;
}

vector<Mark*>* Mark::getAllMarksOfType(Type type) {
	if ((type == X) && (xDatabase->size() > 0)) {
		vector<Mark*>* xXOs = new vector<Mark*>() ;
		for (vector<Mark*>::size_type i = 0 ; i < xDatabase->size() ; i++) {
			xXOs->push_back(xDatabase->at(i)) ;
		}
	}
	else if ((type == O) && (oDatabase->size() > 0)) {
		vector<Mark*>* oXOs = new vector<Mark*>() ;
		for (vector<Mark*>::size_type i = 0 ; i < oDatabase->size() ; i++) {
			oXOs->push_back(oDatabase->at(i)) ;
		}
	}
	return nullptr ;
}




