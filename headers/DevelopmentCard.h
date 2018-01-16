/// \file
/// DevelopmentCard.h
/// DevelopmentCard class derived from Card.

#ifndef DEVELOPMENTCARD_H
#define DEVELOPMENTCARD_H

#include <string> // C++ standard string class
#include <array> //
#include "Card.h" // Building class definition
#include "Enums.h"

/// DevelopmentCard class derived from Card.
///
/// More detailed text.
class DevelopmentCard : public Card {
public:
	/// constructor
	/// \param type Type of development card
	DevelopmentCard(Devtype type);

	/// destructor
	virtual ~DevelopmentCard() = default; 

	/// getter type
	/// \return type
	Devtype getType() const;

	/// check whether the dev card was played
	/// \return boolean 
	bool checkplayedcard() const;

	/// activate dev card
	void playcard();

	/// draw function 
	virtual void draw() const override;

	/// textual info
	/// \return string info
	virtual std::string toString() const override;
private:
	/// type of dev card
	Devtype type;

	/// flag played/not played
	bool played{ 0 };
};

#endif // DEVELOPMENTCARD_H

