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
	virtual ~Card() = default;

	/// draw function
	virtual void draw() const = 0;

	/// textual info
	virtual std::string toString() const;  
};

#endif // CARD_H