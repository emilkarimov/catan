// Tile.h
// Tile class
#ifndef TILE_H
#define TILE_H

#include <string> // C++ standard string class
#include <array>
#include "Enums.h"

class Tile {
public:
	Tile(int, int, Terrain, int);
	~Tile() = default; // virtual destructor

	Terrain getTerrainType() const;
	int getDiceNum() const;
	std::array<int, 2> getCoord() const;  

	void draw() const;
	std::string toString() const;
private:
	std::array<int, 2> coord; // coordinates of the tile
	Terrain type;
	int diceNum;
};

#endif // TILE_H


