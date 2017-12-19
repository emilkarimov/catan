/// \file
/// Player.cpp
/// Player class member-function definitions.

#include "Player.h" // Player class definition
#include <iostream>
using namespace std;

// build costs
std::array<unsigned int, 5> ROAD_COST{ 0, 1, 0, 1, 0 };
std::array<unsigned int, 5> SETTLEMENT_COST{ 1, 1, 1, 1, 0 };
std::array<unsigned int, 5> CITY_COST{ 2, 0, 0, 0, 3 };
std::array<unsigned int, 5> DEV_COST{ 1, 0, 1, 0, 1 };

// constructor 
Player::Player(string name, Color color)
	: name(name), color(color) {}

// add resource
void Player::addResource(Resource type, unsigned int quantity) {
	switch (type) {
	case GRAIN:
		for (unsigned int i{ 0 }; i < quantity; ++i) {
			grain.push_back(ResourceCard(GRAIN));
		}
		break;

	case BRICK:
		for (unsigned int i{ 0 }; i < quantity; ++i) {
			brick.push_back(ResourceCard(BRICK));
		}
		break;

	case WOOL:
		for (unsigned int i{ 0 }; i < quantity; ++i) {
			wool.push_back(ResourceCard(WOOL));
		}
		break;

	case LUMBER:
		for (unsigned int i{ 0 }; i < quantity; ++i) {
			lumber.push_back(ResourceCard(LUMBER));
		}
		break;

	case ORE:
		for (unsigned int i{ 0 }; i < quantity; ++i) {
			ore.push_back(ResourceCard(ORE));
		}
		break;

	default:
		break;
	}

}

// remove resource
void Player::removeResource(Resource type, unsigned int quantity) {
	switch (type) {
	case GRAIN:
		for (unsigned int i{ 0 }; i < quantity; ++i) {
			grain.pop_back();
		}
		break;

	case BRICK:
		for (unsigned int i{ 0 }; i < quantity; ++i) {
			brick.pop_back();
		}
		break;

	case WOOL:
		for (unsigned int i{ 0 }; i < quantity; ++i) {
			wool.pop_back();
		}
		break;

	case LUMBER:
		for (unsigned int i{ 0 }; i < quantity; ++i) {
			lumber.pop_back();
		}
		break;

	case ORE:
		for (unsigned int i{ 0 }; i < quantity; ++i) {
			ore.pop_back();
		}
		break;

	case NORES:
		break; // add nothing

	default:
		break;
	}

}

// get number of settlements
size_t Player::getNumSettlements() const {
	return settlements.size();
}

// get number of roads
size_t Player::getNumRoads() const {
	return roads.size();
}

// get number of cities
size_t Player::getNumCities() const {
	return cities.size();
}

// get number of victory points
size_t Player::getVictoryPoints() const {
	return getNumSettlements() + 2 * getNumCities();
}

// build a settlement
void Player::buildSettlement(int x, int y, TileIntersection intersec) {
	settlements.push_back(Settlement(x, y, intersec));
}

// build a road
void Player::buildRoad(int x, int y, TileEdge edge) {
	roads.push_back(Road(x, y, edge));
}

// build a city
void Player::buildCity(int x, int y, TileIntersection intersec) {
	cities.push_back(City(x, y, intersec));
}

// to string
std::string Player::toString() const {
	return getName() + ":" +
		"\ncolor: " + (getColor()) +
		"\nroads: " + std::to_string(getNumRoads()) +
		"\n" + toStringRoads() +
		"settlements: " + std::to_string(getNumSettlements()) +
		"\n" + toStringSettlements() +
		"cities: " + std::to_string(getNumCities()) +
		"\nnumber of resources: " + std::to_string(getNumResources()) +
		"\n  grain: " + std::to_string(getNumGrain()) +
		"\n  brick: " + std::to_string(getNumBrick()) +
		"\n  wool: " + std::to_string(getNumWool()) +
		"\n  lumber: " + std::to_string(getNumLumber()) +
		"\n  ore: " + std::to_string(getNumOre()) +
		"\ndevelopment cards: " + std::to_string(getNumDev()) +
		"\nVP: " + std::to_string(getVictoryPoints());
}

// text for all roads
std::string Player::toStringRoads() const {
	std::string stringRoads = {};
	for (const Road& road : roads) {
		stringRoads += "  " + road.toString() + "\n";
	}

	return stringRoads;
}

// text for all settlements
std::string Player::toStringSettlements() const {
	std::string stringSettlements = {};
	for (const Settlement& settlement : settlements) {
		stringSettlements += "  " + settlement.toString() + "\n";
	}

	return stringSettlements;
}

// get name
std::string Player::getName() const {
	return name;
}

// get color
std::string Player::getColor() const {
	switch (color) {
	case RED:
		return "red";
	case GREEN:
		return "green";
	case BLUE:
		return "blue";
	case YELLOW:
		return "yellow";
	default:
		return "wrong color";
	}
}

// get references to roads
const std::vector<Road> Player::getRoads() const {
	return roads;
}

// get references to settlements
const std::vector<Settlement> Player::getSettlements() const {
	return settlements;
}

// get references to cities
const std::vector<City> Player::getCities() const {
	return cities;
}

// get grain number
size_t Player::getNumGrain() const {
	return grain.size();
}

// get brick number
size_t Player::getNumBrick() const {
	return brick.size();
}

// get wool number
size_t Player::getNumWool() const {
	return wool.size();
}

// get lumber number
size_t Player::getNumLumber() const {
	return lumber.size();
}

// get ore number
size_t Player::getNumOre() const {
	return ore.size();
}

// get sum of all the resources
size_t Player::getNumResources() const {
	return getNumGrain() + getNumBrick() + getNumWool() + getNumLumber() + getNumOre();
}

// getter number of special cards
size_t Player::getNumSpecial() const {
	return specialCards.size();
}

// add develompent card
void Player::addDevCard(Devtype type) {
	developmentCards.push_back(DevelopmentCard(type));
}

// get number of development cards
size_t Player::getNumDev() const {
	return developmentCards.size();
}


// can play development card?
bool Player::canPlayDev() {
	if (getNumDev() > 0) {
		return true;
	}
	else {
		return false;
	}
}

// can the player build a settlement?
bool Player::canBuildSettlement() {
	return getNumLumber() >= SETTLEMENT_COST[LUMBER] &&
		getNumBrick() >= SETTLEMENT_COST[BRICK] &&
		getNumGrain() >= SETTLEMENT_COST[GRAIN] &&
		getNumWool() >= SETTLEMENT_COST[WOOL];
}

// can the player build a city?
bool Player::canBuildCity() {
	return getNumGrain() >= CITY_COST[GRAIN] &&
		getNumOre() >= CITY_COST[ORE];
}

// can a player build a road?
bool Player::canBuildRoad() {
	return getNumLumber() >= ROAD_COST[LUMBER] &&
		getNumBrick() >= ROAD_COST[BRICK];
}

// can a player buy a development card?
bool Player::canBuyDev() {
	return getNumGrain() >= DEV_COST[GRAIN] &&
		getNumWool() >= DEV_COST[WOOL] &&
		getNumOre() >= DEV_COST[ORE];
}

/// check if a player has a settlement on specific coord
bool Player::hasSettlementAtCoord(int x, int y, int z) const {
	std::array<int, 3> coord{ x, y, z };
	for (const Settlement& settlement : settlements) {
		if (settlement.getLoc() == coord) {
			return true;
		}
	}
	return false;
}

/// check if a player has a city on specific coord
bool Player::hasCityAtCoord(int x, int y, int z) const {
	std::array<int, 3> coord{ x, y, z };
	for (const City& city : cities) {
		if (city.getLoc() == coord) {
			return true;
		}
	}
	return false;
}

/// check if a player has a settlement or a city on specific coord
bool Player::hasPropertyAtCoord(int x, int y, int z) const {
	return (hasCityAtCoord(x, y, z) || hasSettlementAtCoord(x, y, z));
}