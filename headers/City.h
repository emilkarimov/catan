// City.h
// City class derived from Building.
#ifndef CITY_H
#define CITY_H

#include <string> // C++ standard string class
#include <array> //
#include "Building.h" // Building class definition
#include "Enums.h"

class City : public Building {
public:
	City(int, int, TileIntersection);
	virtual ~City() = default; // virtual destructor

	const std::array<int, 3>& getLoc() const;

	// keyword virtual signals intent to override    
	virtual void draw() const override;
	virtual std::string toString() const override;
private:
	std::array<int, 3> loc;
};

#endif // CITY_H


