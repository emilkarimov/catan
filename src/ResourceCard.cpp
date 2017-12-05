// ResourceCard.cpp
// ResourceCard class member-function definitions.
#include "ResourceCard.h" // Card class definition
using namespace std;

// constructor
ResourceCard::ResourceCard(Resource type) : type(type) {}

Resource ResourceCard::getType() const {
	return type;
}

string ResourceCard::toString() const {
	return "resource Card";
}

void ResourceCard::draw() const {
	cout << "draw resouce card\n";
}
