/// \file
/// SpecialCard.h
/// SpecialCard class derived from Card.
#ifndef SPECIALCARD_H
#define SPECIALCARD_H

#include <string> // C++ standard string class
#include <array> //
#include "Card.h" // Building class definition
#include "Enums.h"

class SpecialCard : public Card {
public:
	SpecialCard(SpecialType);
	virtual ~SpecialCard() = default; // virtual destructor

	SpecialType getType() const;

	// keyword virtual signals intent to override    
	virtual void draw() const override;
	virtual std::string toString() const override;
private:
	SpecialType type;
};

#endif // SPECIALCARD_H