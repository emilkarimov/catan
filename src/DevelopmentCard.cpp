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
	Devtype type{ getType() };
	string s;
	switch (type) {
	case KNIGHT:
		s = "KNIGHT";
		break;
	case VICTORY:
		s = "VICTORY";
		break;
	case ROADBUILDING:
		s = "ROADBUILDING";
		break;
	case YEAROFPLENTY:
		s = "YEAROFPLENTY";
		break;
	case MONOPOLY:
		s = "MONOPOLY";
		break;
	default:
		s = "error";
		break;
	}
	return s;
}

void DevelopmentCard::draw() const {
	cout << "draw development card\n";
}

bool DevelopmentCard::checkplayedcard() const {
	return played;
}
void DevelopmentCard::playcard(bool a) {
	played = a;
}
