// Settlement.h
// Settlement class derived from Building.
#ifndef SETTLEMENT_H
#define SETTLEMENT_H

#include <string> // C++ standard string class
#include <array> //
#include "Building.h" // Building class definition

class Settlement : public Building {
public:
	Settlement();
	virtual ~Settlement() = default; // virtual destructor

	void setLoc(int, int, int);
	std::array<int, 3> getLoc() const;

	// keyword virtual signals intent to override    
	virtual void draw() const override;
	virtual std::string toString() const override;
	virtual void check_location() const override;
private:
	std::array<int, 3> cornerLoc;
};

#endif // SETTLEMENT_H

