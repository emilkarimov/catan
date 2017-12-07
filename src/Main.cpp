#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <map>
#include <iostream>

#include "Building.h"
#include "City.h"
#include "Settlement.h"
#include "Road.h"
#include "Enums.h"
#include "Player.h"
using namespace std;

void rollDice();

int main()
{
	cout << "create players" << "\n";
	// create players
	Player player1 = Player("Emil", RED);
	Player player2 = Player("Bram", GREEN);
	Player player3 = Player("Alex", BLUE);
	Player player4 = Player("John", YELLOW);
	array<Player*, 4> players{&player1, &player2, &player3, &player4}; // player pointers are in the array

	// display initial info about each player
	cout << "Initial info about players: \n\n";
	for (Player* playerPtr : players) {
		cout << playerPtr->toString() << "\n\n";
	}

	// add two roads to player1
	player1.buildRoad(0, 1, RIGHT);
	player1.buildRoad(-2, -2, UP);
	//cout << player1.toString() << "\n\n";

	// print the roads
	for (const Road& roadRef : player1.getRoads()) {
		cout << roadRef.toString() << "\n\n";
	}

	// add two settlements to player1
	player1.buildSettlement(-2, -2, TOP);
	player1.buildSettlement(1, 2, BOTTOM);

	// print the settlements
	for (const Settlement& settlementRef : player1.getSettlements()) {
		cout << settlementRef.toString() << "\n\n";
	}
	cout << player1.toString() << "\n\n";

	// add one city to player1
	player1.buildCity(5, 6, BOTTOM);

	// test of getLoc function
	std::array<int, 3> testArray = player1.getSettlements()[1].getLoc();
	cout << "testArray: " << testArray[0] << "\n\n";

	// add resources to player 1
	player1.addResource(GRAIN, 1);
	player1.addResource(BRICK, 1);
	player1.addResource(WOOL, 1);
	player1.addResource(LUMBER, 0);
	player1.addResource(ORE, 1);
	cout << player1.toString() << "\n\n";


	return 0;
}

void rollDice()
{
	int die1, die2;
	for (int i = 0; i < 20; i++)
	die1 = (rand() % 6) + 1;
	die2 = (rand() % 6) + 1;
	cout << die1 << " " << die2 << "\n";
}