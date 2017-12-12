/// \file
/// Tile.h
/// Tile class
#ifndef TILE_H
#define TILE_H

#include <string> // C++ standard string class
#include <array>
#include "Enums.h"

/// Player class
///
/// More detailed text.
class Tile {
public:
	/// constructor
	Tile(int, int, Terrain, int);

	/// destructor
	~Tile() = default; // virtual destructor

					   /// getter type of tile
	Terrain getTerrainType() const;

	/// getter number of tile
	int getDiceNum() const;

	/// getter coordinates of tile
	std::array<int, 2> getCoord() const;

	/// draw function
	void draw() const;

	/// textual info
	std::string toString() const;

	/// get neighbor coordinates
	std::array<int, 2> getNeighborCoord(int neighbor) const;

	/// type of resource the tile produces
	Resource produces() const;

private:
	/// coordinates of the tile
	std::array<int, 2> coord;

	/// type of the tile
	Terrain type;

	/// dice number of the tile
	int diceNum;
};

#endif // TILE_H


