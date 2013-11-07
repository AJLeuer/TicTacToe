
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
	if (this->getXO() == X) {
		vector<Location>* xlocs = new vector<Location>() ;
		for(unsigned int i = 0 ; i < xDatabase.size() ; i++) {
			if (((((xDatabase.at(i))->getLocation()).x) == (this->getLocation().x)) && ((((xDatabase.at(i))->getLocation()).y) == (this->getLocation().y))) {
				xlocs->push_back((xDatabase.at(i)->getLocation())) ;
			}
		}
		return xlocs ;
	}
	else if (this->getXO() == O) {
		vector<Location>* olocs = new vector<Location>() ;
		for(unsigned int i = 0 ; i < xDatabase.size() ; i++) {
			if (((((oDatabase.at(i))->getLocation()).x) == (this->getLocation().x)) && ((((oDatabase.at(i))->getLocation()).y) == (this->getLocation().y))) {
				olocs->push_back((oDatabase.at(i)->getLocation())) ;
			}
		}
		return olocs ;
	}
	return nullptr;
}