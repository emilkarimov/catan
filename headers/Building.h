// Building.h
// Building abstract base class.
// git change
#ifndef BUILDING_H
#define BUILDING_H

#include <string> // C++ standard string class

class Building {
public:
	Building();
	virtual ~Building() = default; // compiler generates virtual destructor

	virtual void draw() const = 0; // pure virtual          
	virtual std::string toString() const; // virtual    

private:
};

#endif // BUILDING_H
