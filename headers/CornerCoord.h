/// \file
/// CornerCoord.h
/// Settlement class derived from Building.
#ifndef CORNERCOORD_H
#define CORNERCOORD_H

#include <string> // C++ standard string class
#include <array> //
#include "Enums.h"
#include <iostream>

class CornerCoord {
public:
	/// constructor
	CornerCoord(int x, int y, TileIntersection z)
		: x(x), y(y), z(z) {}

	/// destructor
	virtual ~CornerCoord() = default; // virtual destructor

	/// textual info
	std::string toString() const;

	int getX() const {
		return x;
	}

	int getY() const {
		return y;
	}

	int getZ() const {
		return z;
	}

	/// == operator
	bool operator==(const CornerCoord& coord) const {
		if ((x == coord.getX()) && (y == coord.getY()) && (z == coord.getZ())) {
			return true;
		}
		return false;
	}

	/// != operator
	bool operator!=(const CornerCoord& coord) const {
		if (*this == coord) {
			return false;
		}
		return true;
	}


private:
	/// location of the settlement
	int x;
	int y;
	TileIntersection z;
};

#endif // CORNERCOORD_H


