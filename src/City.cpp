// City.cpp
// City class member-function definitions.

#include "City.h" // City class definition
#include <iostream>
using namespace std;

// constructor 
City::City(int x, int y, TileIntersection intersect)
	: Building() {
	loc[0] = x;
	loc[1] = y;
	loc[2] = intersect;
}

// get location
const std::array<int, 3>& City::getLoc() const {
	return loc;
}

// draw
void City::draw() const {
	cout << "draw City\n";
}

// to string
std::string City::toString() const {
	return "this is a city with coordinates: " +
		std::to_string(loc[0]) + " " +
		std::to_string(loc[1]) + " " +
		std::to_string(loc[2]);
}