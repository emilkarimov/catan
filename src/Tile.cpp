/// \file
/// Tile.cpp
/// Tile class member-function definitions.

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
	return "this is a Tile " + std::to_string(coord[0]) + " " + std::to_string(coord[1]);
}

// get coordinates of a specific neighbor
std::array<int, 2> Tile::getNeighborCoord(int neighbor) const {
	array<int, 2> neighborCoord;
	switch (neighbor) {
	case 1:
		neighborCoord[0] = coord[0] + 1;
		neighborCoord[1] = coord[1] + 1;
		break;
	case 2:
		neighborCoord[0] = coord[0] + 1;
		neighborCoord[1] = coord[1];
		break;
	case 3:
		neighborCoord[0] = coord[0];
		neighborCoord[1] = coord[1] - 1;
		break;
	case 4:
		neighborCoord[0] = coord[0] - 1;
		neighborCoord[1] = coord[1] - 1;
		break;
	case 5:
		neighborCoord[0] = coord[0] - 1;
		neighborCoord[1] = coord[1];
		break;
	case 6:
		neighborCoord[0] = coord[0];
		neighborCoord[1] = coord[1] + 1;
		break;
	default:
		neighborCoord[0] = -999;
		neighborCoord[1] = -999;
		break;
	}
	return neighborCoord;
}

Resource Tile::produces() const {
	switch (getTerrainType()) {
	case DESERT:
		return NORES;
	case FIELDS:
		return GRAIN;
	case HILLS:
		return BRICK;
	case PASTURE:
		return WOOL;
	case FOREST:
		return LUMBER;
	case MOUNTAINS:
		return ORE;
	case SEA:
		return NORES;
	default:
		return NORES;
	}
}