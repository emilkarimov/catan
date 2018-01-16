/// \file
/// Building.h
/// Building abstract base class.
#ifndef BUILDING_H
#define BUILDING_H

#include <string> // C++ standard string class

/// Building abstract base class.
///
/// More detailed text.
class Building {
public:
	/// constructor
	Building();

	/// destructor
	virtual ~Building() = default; // compiler generates virtual destructor

    /// draw function
	virtual void draw() const = 0; // pure virtual  

	/// text function
	virtual std::string toString() const; // virtual    

private:
};

#endif // BUILDING_H