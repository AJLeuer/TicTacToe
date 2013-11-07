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
	this->location.x = -500 ;
	this->location.y = -500 ;
}

SmartXO::SmartXO(XO xorO, int xloc, int yloc) {
	(this->xo) = xorO ;
	id = (iDs++) ;
	this->location.x = xloc ;
	this->location.y = yloc ;
	
	SmartXO *sxop = this ;
	if(this->getXO() == X) {
		xDatabase.push_back(sxop) ;
	}
	else if(this->getXO() == O) {
		oDatabase.push_back(sxop) ;
	}
	cleanDB() ;
}

void SmartXO::cleanDB() {
	
	vector<SmartXO*>::iterator itr = xDatabase.begin();
	while(itr != xDatabase.end()) {
		if (((itr.operator*())->getXO()) != X) {
			itr = xDatabase.erase(itr) ;
		}
		else {
			itr++ ;
		}
	}
	
	itr = oDatabase.begin();
	while(itr != oDatabase.end()) {
		if (((itr.operator*())->getXO()) != O) {
			itr = oDatabase.erase(itr) ;
		}
		else {
			itr++ ;
		}
	}
}


void SmartXO::operator=(XO xorO) {
	
	(this->xo) = xorO ;
	SmartXO *sxop = this ;
	if(this->getXO() == X) {
		xDatabase.push_back(sxop) ;
	}
	else if(this->getXO() == O) {
		oDatabase.push_back(sxop) ;
	}
	cleanDB() ;
	
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
	SmartXO* Xo = new SmartXO(xO, -499, -499) ;
	return (char)(Xo->getXO()) ;
}

vector<Location>* SmartXO::getAllXOType() {
	
	//cleanDB() ;
	
	XO txo = this->getXO() ;

	if (txo == X) {
		vector<Location>* xlocs = new vector<Location> ;
		for(vector<SmartXO*>::size_type i = 0 ; i < xDatabase.size() ; i++) {
			Location dbLoc = (xDatabase.at(i))->getLocation() ;
			xlocs->push_back(dbLoc) ;
		}
		return xlocs ;
	}
	
	else if (txo == O) {
		vector<Location>* olocs = new vector<Location> ;
		for(vector<SmartXO*>::size_type i = 0 ; i < oDatabase.size() ; i++) {
			Location dbLoc = (oDatabase.at(i))->getLocation() ;
			olocs->push_back(dbLoc) ;
		}
		return olocs ;
	}
	
	return nullptr ;
}