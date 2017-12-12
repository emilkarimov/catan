/// \file
/// Robber.cpp
/// Robber class member-function definitions.

#include "Robber.h" // Robber class definition
#include <iostream>
using namespace std;

// constructor 
Robber::Robber(int x, int y) {
	loc[0] = x;
	loc[1] = y;
}

// get location
const std::array<int, 2>& Robber::getLoc() const {
	return loc;
}

// set location
void Robber::setLoc(int x, int y) {
	loc[0] = x;
	loc[1] = y;
}

// draw
void Robber::draw() const {
	cout << "draw Robber\n";
}

// to string
std::string Robber::toString() const {
	return "this is the Robber";
}