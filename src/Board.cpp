/// \file
/// Board.cpp
// Board class member-function definitions.

#include "Board.h" // Tile class definition
#include <iostream>
using namespace std;

// constructor 
Board::Board(std::vector<Tile> tiles)
	: tiles(tiles) {}

// draw
void Board::draw() const {
	cout << "draw Board\n";
}

// to string
std::string Board::toString() const {
	return "this is a Board";
}

// find tile with specific x y coordinates and return the reference
Tile* Board::getTile(int x, int y) {
	for (Tile& tileRef : tiles) {
		if (tileRef.getCoord()[0] == x && tileRef.getCoord()[1] == y) {
			return &tileRef;
		}
	}
	return nullptr; // return tilePtr if the coordinates are not correct
}