/// \file
/// SpecialCard.cpp
/// SpecialCard class member-function definitions.
#include "SpecialCard.h" // Card class definition
#include <iostream>

using namespace std;

// constructor
SpecialCard::SpecialCard(SpecialType type) : type(type) {}

// getter type
SpecialType SpecialCard::getType() const {
	return type;
}

// text info
string SpecialCard::toString() const {
	return "Special card";
}

// draw
void SpecialCard::draw() const {
	cout << "draw special card\n";
}
