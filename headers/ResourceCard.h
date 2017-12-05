// ResourceCard.h
// ResourceCard class derived from Card.
#ifndef RESOURCECARD_H
#define RESOURCECARD_H

#include <string> // C++ standard string class
#include <array> //
#include "Card.h" // Building class definition
#include "Enums.h"

class ResourceCard : public Card {
public:
	ResourceCard(Resource);
	virtual ~ResourceCard() = default; // virtual destructor

	Resource getType() const;

	// keyword virtual signals intent to override    
	virtual void draw() const override;
	virtual std::string toString() const override;
private:
	Resource type;
};

#endif // RESOURCECARD_H

