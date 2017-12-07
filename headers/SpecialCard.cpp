// SpecialCard.cpp
// SpecialCard class member-function definitions.
#include "SpecialCard.h" // Card class definition
#include <iostream>

using namespace std;

// constructor
SpecialCard::SpecialCard(SpecialType type) : type(type) {}

SpecialType SpecialCard::getType() const {
	return type;
}

string SpecialCard::toString() const {
	return "Special card";
}

void SpecialCard::draw() const {
	cout << "draw special card\n";
}
