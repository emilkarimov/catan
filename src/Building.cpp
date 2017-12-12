/// \file
/// Building.cpp
/// Abstract-base-class Building member-function definitions.

#include "Building.h" // Building class definition
using namespace std;

// constructor
Building::Building() {
}

// toString Building's information (virtual, but not pure virtual)
string Building::toString() const {
	return "Some unspecified Building";
}
