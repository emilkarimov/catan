/// \file
/// Enums.h
/// Enumeration types


#ifndef ENUMS_H
#define ENUMS_H

/// enum to denote the type of tiles
enum Terrain { DESERT, FIELDS, HILLS, PASTURE, FOREST, MOUNTAINS, SEA };

/// enum for type of resource
enum Resource { GRAIN, BRICK, WOOL, LUMBER, ORE, NORES };

/// enum for type of development card
enum Devtype { KNIGHT, VICTORY, ROADBUILDING, YEAROFPLENTY, MONOPOLY };

/// enum for type of special card
enum SpecialType { LONGESTROAD, LARGESTARMY };

/// enum for coordinates of intersection (used to specify the location for settlements and cities)
enum TileIntersection { TOP, BOTTOM };

/// enum for coordinates, used to specify the location of the road
enum TileEdge { UP, RIGHT, DOWN };

/// enum for possible colors for the players
enum Color { RED, GREEN, BLUE, YELLOW };

/// enum for turn stages
enum TurnStage { START, ROLLED};

/// build costs in GRAIN, BRICK, WOOL, LUMBER, ORE;
//std::array<unsigned int, 5> ROAD_COST{ 0, 1, 0, 1, 0 };
//std::array<unsigned int, 5> SETTLEMENT_COST{ 1, 1, 1, 1, 0 };
//std::array<unsigned int, 5> CITY_COST{ 2, 0, 0, 0, 3 };
//std::array<unsigned int, 5> DEV_COST{ 1, 0, 1, 0, 1 };

#endif // ENUMS_H
