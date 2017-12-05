// Building.h
// Building abstract base class.
#ifndef BUILDING_H
#define BUILDING_H

#include <string> // C++ standard string class

class Building {
public:
	Building();
	virtual ~Building() = default; // compiler generates virtual destructor

	virtual void draw() const = 0; // pure virtual          
	virtual std::string toString() const; // virtual    
	virtual void check_location() const = 0; // pure virtual
	bool isOnBoard() const;

private:
	bool onBoard;
};

#endif // BUILDING_H