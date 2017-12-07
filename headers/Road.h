// Road.h
// Road class derived from Building.
#ifndef ROAD_H
#define ROAD_H

#include <string> // C++ standard string class
#include <array> //
#include "Building.h" // Building class definition
#include "Enums.h"

class Road : public Building {
public:
	Road(int, int, TileEdge);

	const std::array<int, 3>& getLoc() const;

	// keyword virtual signals intent to override    
	virtual void draw() const override;
	virtual std::string toString() const override;    
private:
	std::array<int, 3> loc;
};

#endif // ROAD_H
