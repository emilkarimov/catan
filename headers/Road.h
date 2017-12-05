// Road.h
// Road class derived from Building.
#ifndef ROAD_H
#define ROAD_H

#include <string> // C++ standard string class
#include <array> //
#include "Building.h" // Building class definition

class Road : public Building {
public:
	Road();
	virtual ~Road() = default; // virtual destructor

	void setLoc(int, int);
	std::array<int, 2> getLoc() const;

	// keyword virtual signals intent to override    
	virtual void draw() const override;
	virtual std::string toString() const override;    
	virtual void check_location() const override;
private:
	std::array<int, 2> edgeLoc;
};

#endif // ROAD_H
