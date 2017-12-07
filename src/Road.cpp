// Road.cpp
// Road class member-function definitions.

#include "Road.h" // Road class definition
#include <iostream>
using namespace std;

// constructor 
Road::Road(int x, int y, TileEdge edge)
	: Building() {
	loc[0] = x;
	loc[1] = y;
	loc[2] = edge;
}

// get location
const std::array<int, 3>& Road::getLoc() const {
	return loc;
}

// draw
void Road::draw() const {
	cout << "draw road\n";
}

// to string
std::string Road::toString() const {
	return "this is a road with coordinates: " + std::to_string(getLoc()[0]) + 
		" " + std::to_string(getLoc()[1]) + " " + std::to_string(getLoc()[2]);
}