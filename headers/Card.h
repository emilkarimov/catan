/// \file
/// Card.h
/// Card abstract base class.
#ifndef CARD_H
#define CARD_H

#include <string> // C++ standard string class

/// Building abstract base class.
///
/// More detailed text.
class Card {
public:
	/// constructor
	Card();
	/// destructor
	virtual ~Card() = default; // compiler generates virtual destructor

							   /// draw function
	virtual void draw() const = 0; // pure virtual    

								   /// textual info
	virtual std::string toString() const; // virtual    
};

#endif // CARD_H