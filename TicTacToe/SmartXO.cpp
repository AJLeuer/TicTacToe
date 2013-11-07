
#include "SmartXO.h"

using namespace std ;

Location::Location() {
	x = 0 ;
	y = 0 ;
}

int SmartXO::count = 0 ;
int SmartXO::iDs = 0 ;
vector<SmartXO*> SmartXO::xDatabase = vector<SmartXO*>() ;
vector<SmartXO*> SmartXO::oDatabase = vector<SmartXO*>() ;

SmartXO::SmartXO() {
	;
}

SmartXO::SmartXO(XO xorO, int xloc, int yloc) {
	(this->xo) = xorO ;
	id = iDs ;
	this->location.x = xloc ;
	this->location.y = yloc ;
	
	iDs++ ;
	SmartXO *sxop = this ;
	if(this->getXO() == X)
	xDatabase.push_back(sxop) ;
	else if(this->getXO() == O)
	oDatabase.push_back(sxop) ;
}

void SmartXO::operator=(XO xorO) {
	(this->xo) = xorO ;
	SmartXO *sxop = this ;
	if(this->getXO() == X)
	xDatabase.push_back(sxop) ;
	else if(this->getXO() == O)
	oDatabase.push_back(sxop) ;
}



bool SmartXO::compXO(XO first, XO second) {
	if ((first == blank) || (second == blank))
	return false ;
	else if ((first == X) && (second == X))
	return true ;
	else if ((first == O) && (second == O))
	return true ;
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

vector<Location>* SmartXO::getAllXOType() {
	XO xo = this->getXO() ;
	
	if (xo == X) {
		vector<Location>* xlocs = new vector<Location> ;
		for(vector<SmartXO*>::size_type i = 0 ; i < xDatabase.size() ; i++) {
			Location dbLoc = (xDatabase.at(i))->getLocation() ;
			if (((dbLoc.x) == (this->getLocation().x)) && ((dbLoc.y) == (this->getLocation().y))) {
				xlocs->push_back(dbLoc) ;
			}
			
		}
		return xlocs ;
	}
	else if (xo == O) {
		vector<Location>* olocs = new vector<Location> ;
		for(vector<SmartXO*>::size_type i = 0 ; i < oDatabase.size() ; i++) {
			Location dbLoc = (oDatabase.at(i))->getLocation() ;
			if (((dbLoc.x) == (this->getLocation().x)) && ((dbLoc.y) == (this->getLocation().y))) {
				olocs->push_back(dbLoc) ;
			}
		}
		return olocs ;
	}
	return nullptr;
}