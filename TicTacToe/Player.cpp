//
//  Player.cpp
//  TicTacToe
//
//  Created by Adam James Leuer on 11/10/13.
//  Copyright (c) 2013 Adam James Leuer. All rights reserved.
//

#include "Player.h"

Player::Player() {
	this->name = " " ;
	this->xorO = Type::nullMark ;
	this->human = true ;
	this->nextSpace = nullptr  ;
	this->lastWritten = nullptr ;
}

Player::Player(string name) {
	this->name = name ;
	this->xorO = Type::nullMark ;
	this->human = true ;
	this->nextSpace = nullptr  ;
	this->lastWritten = nullptr ;
}

Player::Player(string name, bool human) {
	this->name = name ;
	this->xorO = Type::nullMark ;
	this->human = human ;
	this->nextSpace = nullptr  ;
	this->lastWritten = nullptr ;
}

Player::Player(string name, Type xOrO, bool human) {
	this->name = name ;
	this->xorO = xOrO ;
	this->human = human ;
	this->nextSpace = nullptr ;
	this->lastWritten = nullptr ;
}

void Player::setXO(Type Xo) {
	this->xorO = Xo ;
}

char Player::getXOChar() {
	return Mark::getMarkType(xorO) ;
}

void Player::setName(string name)  {
	this->name = name ;
}

string Player::getName() {
	return this->name ;
}

void Player::setNextSpace(int x, int y) {
	if (this->getNextSpace() == nullptr) {
		this->nextSpace = new Location() ;
	}
	this->nextSpace->x = x ;
	this->nextSpace->y = y ;
}

Location* Player::getNextSpace() {
	return this->nextSpace ;
}

void Player::setLastWritten(int x, int y) {
	if (this->getLastWritten() == nullptr) {
		this->lastWritten = new Location() ;
	}
	this->lastWritten->x = x ;
	this->lastWritten->y = y ;
}

Location* Player::getLastWritten() {
	return this->lastWritten ;
}

