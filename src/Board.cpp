/// \file
/// Board.cpp
// Board class member-function definitions.

#include "Board.h" // Tile class definition
#include <iostream>
using namespace std;

// constructor 
Board::Board(array<Tile, 37>* a)
	: tilesPtr(a) {}

// draw
void Board::draw() const {
	cout << "draw Board\n";
}

// to string
std::string Board::toString() const {
	return "this is a Board";
}