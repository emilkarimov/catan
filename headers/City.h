/// \file
/// City.h
/// City class derived from Building.
#ifndef CITY_H
#define CITY_H

#include <string> // C++ standard string class
#include <array> //
#include "Building.h" // Building class definition
#include "Enums.h"

/// City class derived from Building.
///
/// More detailed text.
class City : public Building {
public:
	/// constructor
	City(int, int, TileIntersection);

	/// destructor
	virtual ~City() = default;

	/// getter location
	/// \return location
	const std::array<int, 3>& getLoc() const;

	/// draw function 
	virtual void draw() const override;

	/// textual info
	/// \return info string
	virtual std::string toString() const override;
private:
	/// location of the city (x, y, TOP/BOTTOM)
	std::array<int, 3> loc;
};

#endif // CITY_H


