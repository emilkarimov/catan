#pragma once
// DevelopmentCard.h
// DevelopmentCard class derived from Card.
#ifndef DEVELOPMENTCARD_H
#define DEVELOPMENTCARD_H

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
	bool played{ 0 };
};

#endif // DEVELOPMENTCARD_H

