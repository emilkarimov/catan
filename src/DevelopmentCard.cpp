/// \file
/// DevelopmentCard.cpp
/// DevelopmentCard class member-function definitions.
#include "DevelopmentCard.h" // Card class definition
#include <iostream>

using namespace std;

// constructor
DevelopmentCard::DevelopmentCard(Devtype type) : type(type) {}

Devtype DevelopmentCard::getType() const {
	return type;
}

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

void DevelopmentCard::draw() const {
	cout << "draw development card\n";
}

bool DevelopmentCard::checkplayedcard() const {
	return played;
}
void DevelopmentCard::playcard() {
	played = 1;
}
