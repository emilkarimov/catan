/// \file
/// Board.h
/// Board class
///
#ifndef BOARD_H
#define BOARD_H

#include <string> // C++ standard string class
#include <array>
#include "Tile.h"
#include <vector>

/// Board class
///
/// More detailed text.
class Board {
public:
	/// constructor
	/// \param a array with pointers to 37 tiles
	Board(std::vector<Tile> tiles);
	/// destructor
	~Board() = default; // virtual destructor

						/// draw function
	void draw() const;

	/// textual info
	std::string toString() const;

	/// find tile with specific x y coordinates and return the reference
	Tile* getTile(int x, int y);

	/// coordinates of adjacent corners. Actual tiles with these coordinates might not exist
	/// if the corner is on the border 
	std::array<std::array<int, 3>, 3> getAdjacentCorners(int x, int y, TileIntersection intersect);

private:
	/// pointers to tiles
	std::vector<Tile> tiles;
};

#endif // BOARD_H


