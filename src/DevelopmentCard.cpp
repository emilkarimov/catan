// DevelopmentCard.cpp
// DevelopmentCard class member-function definitions.
#include "DevelopmentCard.h" // Card class definition
#include <iostream>

using namespace std;

// constructor
DevelopmentCard::DevelopmentCard(Devtype type) : type(type) {}

Devtype DevelopmentCard::getType() const {
	return type;
}

string DevelopmentCard::toString() const {
	return "development card";
}

void DevelopmentCard::draw() const {
	cout << "draw resouce card\n";
}

bool DevelopmentCard::checkplayedcard() const {
	return played;
}
void DevelopmentCard::playcard(bool a) {
	played = a;
}