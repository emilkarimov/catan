// Board.h
// Board class
#ifndef BOARD_H
#define BOARD_H
//vs change
#include <string> // C++ standard string class
#include <array>
#include "Tile.h"

class Board {
public:
	Board(std::array<Tile, 37>* );
	~Board() = default; // virtual destructor

	void draw() const;
	std::string toString() const;
private:
	std::array<Tile, 37>* tilesPtr;
};

#endif // BOARD_H


