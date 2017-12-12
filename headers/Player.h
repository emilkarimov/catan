/// \file
/// Player.h
/// Player class.
#ifndef PLAYER_H
#define PLAYER_H

#include <string> // C++ standard string class
#include "ResourceCard.h"
#include "DevelopmentCard.h"
#include "Road.h"
#include "Settlement.h"
#include "City.h"
#include <vector>

/// Player class
///
/// More detailed text.
class Player {
public:
	/// constructor
	/// \param name Name of the player
	/// \param color Color of the player
	Player(std::string name, Color color);

	/// destructor
	~Player() = default; // compiler generates virtual destructor

						 /// text info about player
						 /// \return string with info about player
	std::string toString() const;

	/// text for all roads
	std::string toStringRoads() const;

	/// test for all settlements
	std::string toStringSettlements() const;

	/// getter name
	/// \return name
	std::string getName() const;

	/// getter color
	/// \return color
	std::string getColor() const;

	/// getter number of settlements
	size_t getNumSettlements() const;

	/// getter number of roads
	size_t getNumRoads() const;

	/// getter number of cities
	size_t getNumCities() const;

	/// getter number of victory points
	size_t getVictoryPoints() const;

	/// getter number of grain cards
	size_t getNumGrain() const;

	/// getter number of brick cards
	size_t getNumBrick() const;

	/// getter number of wool cards
	size_t getNumWool() const;

	/// getter number of lumber cards
	size_t getNumLumber() const;

	/// getter number of ore cards
	size_t getNumOre() const;

	/// getter total number of resource cards
	size_t getNumResources() const;

	/// getter to access the roads
	/// \return vector of roads the player has. Cannot be modified
	const std::vector<Road> getRoads() const;

	/// getter to access the settlements
	/// \return vector of settlements the player has. Cannot be modified
	const std::vector<Settlement> getSettlements() const;

	/// build road
	/// \param x x coord
	/// \param y y coord
	/// \param edge edge specifier
	void buildRoad(int x, int y, TileEdge edge);

	/// build settlement
	/// \param x x coord
	/// \param y y coord
	/// \param intersec intersection specifier
	void buildSettlement(int x, int y, TileIntersection intersec);

	/// build a city
	/// \param x x coord
	/// \param y y coord
	/// \param intersec intersection specifier
	void buildCity(int, int, TileIntersection);

	/// add a resource of a specific type
	/// \param type type of resource
	/// \param qnt number of cards to be added
	void addResource(Resource type, unsigned int qnt);

	/// remove a resource of a specific type
	/// \param type type of resource
	/// \param qnt number of cards to be removed
	void removeResource(Resource type, unsigned int qnt);


private:
	// buildings
	/// roads
	std::vector<Road> roads;

	/// settlements
	std::vector<Settlement> settlements;

	/// cities
	std::vector<City> cities;

	// resources
	/// grain
	std::vector<ResourceCard> grain;

	///brick
	std::vector<ResourceCard> brick;

	/// wool
	std::vector<ResourceCard> wool;

	/// lumber
	std::vector<ResourceCard> lumber;

	/// ore
	std::vector<ResourceCard> ore;

	/// development cards
	std::vector<DevelopmentCard> developmentCards;

	/// name
	std::string name;

	/// color
	Color color;
};

#endif // PLAYER_H
