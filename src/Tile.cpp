// Tile.cpp
// Tile class member-function definitions.

#include "Tile.h" // Tile class definition
#include <iostream>
using namespace std;

// constructor 
Tile::Tile(int x, int y, Terrain type, int diceNum)
	: type(type), diceNum(diceNum) {
	coord[0] = x;
	coord[1] = y;
}

// get type
Terrain Tile::getTerrainType() const {
	return type;
}

// get dice number
int Tile::getDiceNum() const {
	return diceNum;
}

// get coordinates
std::array<int, 2> Tile::getCoord() const {
	return coord;
}


// draw
void Tile::draw() const {
	cout << "draw Tile\n";
}

// to string
std::string Tile::toString() const {
	return "this is a Tile";
}