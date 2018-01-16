/// \file
/// DevelopmentCard.cpp
/// DevelopmentCard class member-function definitions.
#include "DevelopmentCard.h" // Card class definition
#include <iostream>
using namespace std;

// constructor
DevelopmentCard::DevelopmentCard(Devtype type) : type(type) {

}

// type of dev card
Devtype DevelopmentCard::getType() const {
	return type;
}

// string info
string DevelopmentCard::toString() const {
	switch (type) {
	case KNIGHT:
		return "Knight";
	case VICTORY:
		return "Victory";
	case ROADBUILDING:
		return "Road Building";
	case YEAROFPLENTY:
		return "Year of plenty";
	case MONOPOLY:
		return "Monopoly";
	default:
		return "Undefined Development card";
	}
}

// draw
void DevelopmentCard::draw() const {
	cout << "draw development card\n";
}

// check if the card was played
bool DevelopmentCard::checkplayedcard() const {
	return played;
}

// play the card
void DevelopmentCard::playcard() {
	played = 1;
}

