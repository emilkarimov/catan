/// \file
/// Board.h
/// Board class
///
#ifndef BOARD_H
#define BOARD_H

#include <string> // C++ standard string class
#include <array>
#include "Tile.h"

/// Board class
///
/// More detailed text.
class Board {
public:
	/// constructor
	/// \param a array with pointers to 37 tiles
	Board(std::array<Tile, 37>* a);
	/// destructor
	~Board() = default; // virtual destructor

						/// draw function
	void draw() const;

	/// textual info
	std::string toString() const;
private:
	/// pointers to tiles
	std::array<Tile, 37>* tilesPtr;
};

#endif // BOARD_H


