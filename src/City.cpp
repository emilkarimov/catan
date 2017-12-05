// City.cpp
// City class member-function definitions.

#include "City.h" // City class definition
#include <iostream>
using namespace std;

// constructor 
City::City()
	: Building() {
	cornerLoc[0] = -1;
	cornerLoc[1] = -1;
	cornerLoc[2] = -1;
}

// set location
void City::setLoc(int a, int b, int c) {
	cornerLoc[0] = a;
	cornerLoc[1] = b;
	cornerLoc[2] = c;
}

// get location
std::array<int, 3> City::getLoc() const {
	return cornerLoc;
}

// draw
void City::draw() const {
	cout << "draw City\n";
}

// to string
std::string City::toString() const {
	return "this is a City";
}

// check location ???
void City::check_location() const {
	cout << "check location\n";
}