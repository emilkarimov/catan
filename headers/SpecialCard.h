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
	/// constructor
	SpecialCard(SpecialType);
	virtual ~SpecialCard() = default;

	/// getter type
	SpecialType getType() const;

	/// draw
	virtual void draw() const override;

	/// string info
	virtual std::string toString() const override;
private:
	/// type
	SpecialType type;
};

#endif // SPECIALCARD_H