/// \file
/// LongestRoad.cpp
/// LongestRoad class member-function definitions.

#include "LongRoad.h" // Road class definition
#include <iostream>
using namespace std;

// constructor 
LongRoad::LongRoad(Settlement s1, Settlement s2) {
	roads.push_back(s1);
	roads.push_back(s2);
}

// add road
void LongRoad::addRoad(Settlement s1, bool pos) {
}

// get corner
const Settlement LongRoad::getCorner(int idx) const {
	return roads[idx];
}

// get num of corners in the road
int LongRoad::getNumCorners() {
	return roads.size();
}