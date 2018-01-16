/// \file
/// LongRoad.h
/// LongRoad class
#ifndef LONGROAD_H
#define LONGROAD_H

#include <string> // C++ standard string class
#include <array> //
#include "Enums.h"
#include <vector>
#include "Settlement.h"
#include "Road.h"

/// LongRoad class 
///
/// More detailed text.
class LongRoad {
public:
	/// constructor
	LongRoad(Settlement s1, Settlement s2);

	/// get corner of road
	const Settlement getCorner(int idx) const;

	/// textual info
	std::string toString() const;

	/// add road
	void addRoad(Settlement s1, bool pos);

	/// get size of corners
	int getNumCorners();
private:
	/// location
	std::array<int, 3> loc;

	/// roads
	std::vector<Settlement> roads;
};

#endif // LONGROAD_H
