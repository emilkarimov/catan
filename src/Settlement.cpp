// Settlement.cpp
// Settlement class member-function definitions.

#include "Settlement.h" // Settlement class definition
#include <iostream>
using namespace std;

// constructor 
Settlement::Settlement()
	: Building() {
	cornerLoc[0] = -1;
	cornerLoc[1] = -1;
	cornerLoc[2] = -1;
}

// set location
void Settlement::setLoc(int a, int b, int c) {
	cornerLoc[0] = a;
	cornerLoc[1] = b;
	cornerLoc[2] = c;
}

// get location
std::array<int, 3> Settlement::getLoc() const {
	return cornerLoc;
}

// draw
void Settlement::draw() const {
	cout << "draw Settlement\n";
}

// to string
std::string Settlement::toString() const {
	return "this is a settlement";
}

// check location ???
void Settlement::check_location() const {
	cout << "check location\n";
}