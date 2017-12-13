/// \file
/// Road.cpp
/// Road class member-function definitions.

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
	std::string edgeString{ "" };
	std::array<int, 3> roadLoc = getLoc();
	if (roadLoc[2] == UP) {
		edgeString += "UP";
	}
	else if (roadLoc[2] == RIGHT) {
		edgeString += "RIGHT";
	}
	else if (roadLoc[2] == DOWN) {
		edgeString += "DOWN";
	}
	else {
		edgeString += "ERROR";
	}
	return "r: " + std::to_string(roadLoc[0]) +
		" " + std::to_string(roadLoc[1]) + " " + edgeString;
}