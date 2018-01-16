/// \file
/// ResourceCard.cpp
/// ResourceCard class member-function definitions.
#include "ResourceCard.h" // Card class definition
#include <iostream>
using namespace std;

// constructor
ResourceCard::ResourceCard(Resource type) : type(type) {}

// getter type
Resource ResourceCard::getType() const {
	return type;
}

// string info
string ResourceCard::toString() const {
	return "resource Card";
}

// draw function
void ResourceCard::draw() const {
	cout << "draw resouce card\n";
}
