/// \file
/// Player.cpp
/// Player class member-function definitions.

#include "Player.h" // Player class definition
#include <iostream>
using namespace std;

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
		"\n    grain: " + std::to_string(getNumGrain()) +
		"\n    brick: " + std::to_string(getNumBrick()) +
		"\n    wool: " + std::to_string(getNumWool()) +
		"\n    lumber: " + std::to_string(getNumLumber()) +
		"\n    ore: " + std::to_string(getNumOre()) +
		"\nVP: " + std::to_string(getVictoryPoints());
}

// text for all roads
std::string Player::toStringRoads() const {
	std::string stringRoads = {};
	for (const Road& road : roads) {
		stringRoads += "    " + road.toString() + "\n";
	}

	return stringRoads;
}

// text for all settlements
std::string Player::toStringSettlements() const {
	std::string stringSettlements = {};
	for (const Settlement& settlement : settlements) {
		stringSettlements += "    " + settlement.toString() + "\n";
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