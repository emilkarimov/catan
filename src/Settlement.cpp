/// \file
/// Settlement.cpp
/// Settlement class member-function definitions.

#include "Settlement.h" // Settlement class definition
#include <iostream>
using namespace std;

// constructor 
Settlement::Settlement(int x, int y, TileIntersection intersec)
	: Building() {
	loc[0] = x;
	loc[1] = y;
	loc[2] = intersec;
}

// get location
const std::array<int, 3>& Settlement::getLoc() const {
	return loc;
}

// draw
void Settlement::draw() const {
	cout << "draw Settlement\n";
}

// to string
std::string Settlement::toString() const {
	std::string settlementString{ "" };
	if (loc[2] == TOP) {
		settlementString += "TOP";
	}
	else if (loc[2] == BOTTOM) {
		settlementString += "BOTTOM";
	}
	else {
		settlementString += "ERROR";
	}

	return "s: " +
		std::to_string(loc[0]) + " " +
		std::to_string(loc[1]) + " " +
		settlementString;
}