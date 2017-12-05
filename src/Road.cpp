// Road.cpp
// Road class member-function definitions.

#include "Road.h" // Road class definition
#include <iostream>
using namespace std;

// constructor 
Road::Road()
	: Building() {
	edgeLoc[0] = -1;
	edgeLoc[1] = -1;
}

// set location
void Road::setLoc(int a, int b) {
	edgeLoc[0] = a;
	edgeLoc[1] = b;
}

// get location
std::array<int, 2> Road::getLoc() const {
	return edgeLoc;
}

// draw
void Road::draw() const {
	cout << "draw road\n";
}

// to string
std::string Road::toString() const {
	return "this is road";
}

// check location ???
void Road::check_location() const {
	cout << "check location\n";
}