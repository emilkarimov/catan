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

// coordinates of adjacent corners. Actual tiles with these coordinates might not exist
// if the corner is on the border 
std::array<std::array<int, 3>, 3> Board::getAdjacentCorners(int x, int y, TileIntersection intersect) {
	// there are three adjacent corners always
	std::array<int, 3> cornerLeft;
	std::array<int, 3> cornerMiddle;
	std::array<int, 3> cornerRight;
	std::array<std::array<int, 3>, 3> corners; // array with three corners

	// adjacent corners are different for TOP and BOTTOM intersections
	if (intersect == TOP) {
		// left corner
		cornerLeft[0] = x;
		cornerLeft[1] = y + 1;
		cornerLeft[2] = BOTTOM;

		// middle corner
		cornerMiddle[0] = x + 1;
		cornerMiddle[1] = y + 2;
		cornerMiddle[2] = BOTTOM;

		// right corner
		cornerRight[0] = x + 1;
		cornerRight[1] = y + 1;
		cornerRight[2] = BOTTOM;
	}
	else if (intersect == BOTTOM) {
		// left corner
		cornerLeft[0] = x - 1;
		cornerLeft[1] = y - 1;
		cornerLeft[2] = TOP;

		// middle corner
		cornerMiddle[0] = x - 1;
		cornerMiddle[1] = y - 2;
		cornerMiddle[2] = TOP;

		// right corner
		cornerRight[0] = x;
		cornerRight[1] = y - 1;
		cornerRight[2] = TOP;
	}

	// return array with three corners
	corners[0] = cornerLeft;
	corners[1] = cornerMiddle;
	corners[2] = cornerRight;
	return corners;
}

std::vector<std::array<int, 3>> Board::findCornersAtDiceNum(unsigned int diceNum) {
	std::vector<std::array<int, 3>> corners;
	for (const Tile& tile : tiles) {
		if (tile.getDiceNum() == diceNum) {
			std::array<std::array<int, 3>, 6> sixCorners{ getSixCorners(tile.getCoord()[0], tile.getCoord()[1]) };
			for (auto corner : sixCorners) {
				corners.push_back(corner);
			}
		}
	}

	return corners;
}

std::vector<Tile> Board::findTilesWithDiceNum(unsigned int diceNum) {
	std::vector<Tile> tilesWithDiceNum;
	for (const Tile& tile : tiles) {
		if (tile.getDiceNum() == diceNum) {
			tilesWithDiceNum.push_back(tile);
		}
	}

	return tilesWithDiceNum;
}


std::array<std::array<int, 3>, 6> Board::getSixCorners(int x, int y) {
	// coordinates of the six corners
	std::array<int, 3> c1{ x, y, TOP };
	std::array<int, 3> c2{ x + 1, y + 1, BOTTOM };
	std::array<int, 3> c3{ x, y - 1, TOP };
	std::array<int, 3> c4{ x, y, BOTTOM };
	std::array<int, 3> c5{ x - 1, y - 1, TOP };
	std::array<int, 3> c6{ x, y + 1, BOTTOM };

	// put all 6 corners in one array
	std::array<std::array<int, 3>, 6> allCorners{ c1, c2, c3, c4, c5, c6 };

	return allCorners;
}

std::vector<Tile> Board::getTiles() const {
	return tiles;
}

// checks whether the board has a tile with xy coordinates
bool Board::hasTile(int x, int y) {
	for (Tile& tileRef : tiles) {
		if (tileRef.getCoord()[0] == x && tileRef.getCoord()[1] == y) {
			return true;
		}
	}
	return false; // return false if there are no tiles with such coordinates
}