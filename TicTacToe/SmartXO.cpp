#include <iterator>

#include "SmartXO.h"


using namespace std ;

Location::Location() {
	x = 0 ;
	y = 0 ;
}


unsigned iDs = 0 ;

vector<SmartXO*> xDatabase = vector<SmartXO*>() ;
vector<SmartXO*> oDatabase = vector<SmartXO*>() ;

SmartXO::SmartXO() {
	this->xo = blank ;
	this->id = -500 ;
	this->location.x = -500 ;
	this->location.y = -500 ;
	this->on_board = false ;
}

SmartXO::SmartXO(XO xorO, int xloc, int yloc, bool ob) {
	(this->xo) = xorO ;
	this->id = (iDs++) ;
	this->location.x = xloc ;
	this->location.y = yloc ;
	this->on_board = ob ;
	
	SmartXO *sxop = this ;
	if(this->getXO() == X) {
		xDatabase.push_back(sxop) ;
	}
	else if(this->getXO() == O) {
		oDatabase.push_back(sxop) ;
	}
}



void SmartXO::operator=(XO xorO) {
	
	(this->xo) = xorO ;
	SmartXO *sxop = this ;
	if (this->on_board) {
		if(this->getXO() == X) {
			xDatabase.push_back(sxop) ;
		}
		else if(this->getXO() == O) {
			oDatabase.push_back(sxop) ;
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
		for(vector<SmartXO*>::size_type i = 0 ; i < xDatabase.size() ; i++) {
			if (xDatabase.at(i)->on_board) {
				Location dbLoc = (xDatabase.at(i))->getLocation() ;
				xlocs->push_back(dbLoc) ;
			}
		}
		return xlocs ;
	}
	else if (txo == O) {
		vector<Location>* olocs = new vector<Location> ;
		for(vector<SmartXO*>::size_type i = 0 ; i < oDatabase.size() ; i++) {
			if (oDatabase.at(i)->on_board) {
				Location dbLoc = (oDatabase.at(i))->getLocation() ;
				olocs->push_back(dbLoc) ;
			}
		}
		return olocs ;
	}
	return nullptr ;
}