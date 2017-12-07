// Player.h
// Player class.
#ifndef PLAYER_H
#define PLAYER_H

#include <string> // C++ standard string class
#include "ResourceCard.h"
#include "DevelopmentCard.h"
#include "Road.h"
#include "Settlement.h"
#include "City.h"
#include <vector>

class Player {
public:
	Player(std::string name, Color color);
	~Player() = default; // compiler generates virtual destructor
        
	std::string toString() const;
	std::string getName() const;
	Color getColor() const;

	size_t getNumSettlements() const;
	size_t getNumRoads() const;
	size_t getNumCities() const;
	size_t getVictoryPoints() const;
	size_t getNumGrain() const;
	size_t getNumBrick() const;
	size_t getNumWool() const;
	size_t getNumLumber() const;
	size_t getNumOre() const;
	size_t getNumResources() const;

	const std::vector<Road> getRoads() const;
	const std::vector<Settlement> getSettlements() const;

	void buildRoad(int, int, TileEdge);
	void buildSettlement(int, int, TileIntersection);
	void buildCity(int, int, TileIntersection);

	void addResource(Resource type, unsigned int qnt);
	void removeResource(Resource type, unsigned int qnt);


private:
	// buildings
	std::vector<Road> roads;
	std::vector<Settlement> settlements;
	std::vector<City> cities;

	// resources
	std::vector<ResourceCard> grain;
	std::vector<ResourceCard> brick;
	std::vector<ResourceCard> wool;
	std::vector<ResourceCard> lumber;
	std::vector<ResourceCard> ore;

	std::vector<DevelopmentCard> developmentCards;

	std::string name;
	Color color;
};

#endif // PLAYER_H
