/// \file
/// ResourceCard.h
/// ResourceCard class derived from Card.
#ifndef RESOURCECARD_H
#define RESOURCECARD_H

#include <string> // C++ standard string class
#include <array> //
#include "Card.h" // Building class definition
#include "Enums.h"

/// ResourceCard class
///
/// More detailed text.
class ResourceCard : public Card {
public:
	/// constructor
	/// \param type type of resource
	ResourceCard(Resource type);

	/// destructor
	virtual ~ResourceCard() = default;

	/// getter type
	Resource getType() const;

	/// draw function  
	virtual void draw() const override;

	/// textual info
	///return info string
	virtual std::string toString() const override;
private:
	/// type of resource card
	Resource type;
};

#endif // RESOURCECARD_H

