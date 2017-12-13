/// \file
/// Card.cpp
/// Abstract-base-class Card member-function definitions.

#include "Card.h" // Card class definition
using namespace std;

// constructor
Card::Card() {}

// toString Card's information (virtual, but not pure virtual)
string Card::toString() const {
	return "Some unspecified Card";
}
