/// \file
/// Settlement.h
/// Settlement class derived from Building.
#ifndef SETTLEMENT_H
#define SETTLEMENT_H

#include <string> // C++ standard string class
#include <array> //
#include "Building.h" // Building class definition
#include "Enums.h"

/// Settlement class derived from Building.
///
/// More detailed text.
class Settlement : public Building {
public:
	/// constructor
	Settlement(int, int, TileIntersection);

	/// destructor
	virtual ~Settlement() = default; 

	/// getter location
	const std::array<int, 3>& getLoc() const;

	/// draw function   
	virtual void draw() const override;

	/// textual info
	virtual std::string toString() const override;
private:
	/// location of the settlement
	std::array<int, 3> loc;
};

#endif // SETTLEMENT_H

