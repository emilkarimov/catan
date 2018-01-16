/// \file
/// DevCardDeck.h
/// DevelopmentCard deck class.

#ifndef DEVCARDDECK_H
#define DEVCARDDECK_H

#include <string> // C++ standard string class
#include <array> //
#include <vector>
#include "DevelopmentCard.h"
#include "Player.h"

/// DevelopmentCard deck class.
///
/// More detailed text.
class DevCardDeck {
public:
	/// default constructor
	/// development card deck
	DevCardDeck() = default;

	/// destructor
	~DevCardDeck() = default;

	/// initialize deck
	void initDeck();

	/// buy dev card
	void buyDevelopmentCard(Player& player);

	/// add dev card
	void addDevelopmentCard(Devtype type);

	/// draw function 
	virtual void draw() const ;

	/// textual info
	/// \return string info
	virtual std::string toString() const ;
private:
	/// type of dev card
	std::vector<DevelopmentCard> deck;
};

#endif // DEVCARDDECK_H

