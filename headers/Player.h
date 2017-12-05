// Player.h
// Player class.
#ifndef PLAYER_H
#define PLAYER_H

#include <string> // C++ standard string class

class Player {
public:
	Player(std::string name, int color);
	~Player() = default; // compiler generates virtual destructor
        
	std::string toString() const;
	std::string getName() const;

	int getNumSettlements() const;
	int getNumRoads() const;
	int getNumCities() const;

	void updateResource(Resource type, int quantity);


private:
	std::vector<Road *> roads;
	std::vector<Settlement *> settlements;
	std::vector<City *> cities;

	std::vector<ResourceCard *>;
	std::vector<DevelopmentCard *>;
	std::vector<SpecialCard *>;
};

#endif // PLAYER_H
