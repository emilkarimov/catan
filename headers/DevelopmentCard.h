#pragma once
// ResourceCard.h
// ResourceCard class derived from Card.
#ifndef RESOURCECARD_H
#define RESOURCECARD_H

#include <string> // C++ standard string class
#include <array> //
#include "Card.h" // Building class definition
#include "Enums.h"

class DevelopmentCard : public Card {
public:
	DevelopmentCard(Devtype);
	virtual ~DevelopmentCard() = default; // virtual destructor

	Devtype getType() const;
	bool checkplayedcard() const;
	void playcard(bool);

	// keyword virtual signals intent to override    
	virtual void draw() const override;
	virtual std::string toString() const override;
private:
	Devtype type;
	bool played{ false };
};

#endif // RESOURCECARD_H

//something
