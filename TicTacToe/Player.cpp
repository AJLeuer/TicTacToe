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
	this->xorO = XO::nullxo ;
	this->human = true ;
	this->nextSpace = new Location(500, 500) ;
}

Player::Player(string name) {
	this->name = name ;
	this->xorO = XO::nullxo ;
	this->human = true ;
	this->nextSpace = new Location(500, 500) ;
}

Player::Player(string name, bool human) {
	this->name = name ;
	this->xorO = XO::nullxo ;
	this->human = human ;
	this->nextSpace = new Location(500, 500) ;
}

Player::Player(string name, XO xOrO, bool human) {
	this->name = name ;
	this->xorO = xOrO ;
	this->human = human ;
	this->nextSpace = new Location(500, 500) ;
}

void Player::setXO(XO Xo) {
	this->xorO = Xo ;
}

char Player::getXOChar() {
	return SmartXO::getXOChar(xorO) ;
}

void Player::setName(string name)  {
	this->name = name ;
}

string Player::getName() {
	return this->name ;
}

void Player::setNextSpace(int x, int y) {
	this->nextSpace->x = x ;
	this->nextSpace->y = y ;
}

Location Player::getNextSpace() {
	return *this->nextSpace ;
}


