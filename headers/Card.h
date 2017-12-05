// Card.h
// Card abstract base class.
#ifndef CARD_H
#define CARD_H

#include <string> // C++ standard string class

class Card {
public:
	Card();
	virtual ~Card() = default; // compiler generates virtual destructor

	virtual void draw() const = 0; // pure virtual          
	virtual std::string toString() const; // virtual    
};

#endif // CARD_H