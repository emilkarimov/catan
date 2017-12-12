/// \file
/// Road.h
/// Road class derived from Building.
#ifndef ROAD_H
#define ROAD_H

#include <string> // C++ standard string class
#include <array> //
#include "Building.h" // Building class definition
#include "Enums.h"

/// Road class derived from Building.
///
/// More detailed text.
class Road : public Building {
public:
	/// constructor
	Road(int, int, TileEdge);

	/// getter location
	const std::array<int, 3>& getLoc() const;

	/// draw function
	virtual void draw() const override;

	/// textual info
	virtual std::string toString() const override;
private:
	/// location
	std::array<int, 3> loc;
};

#endif // ROAD_H
