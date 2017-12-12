/// \file
/// Main.cpp

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
#include "Tile.h"
#include "Robber.h"
#include "GameEngine.h"

using namespace std;

void rollDice();
void iterOneCheck();
void testFirstStage();
vector<Tile> createDefaultTiles();
vector<Player> createDefaultPlayers();

int main()
{
	// player initialisation
	Player player = Player("Alex", RED);
	player.buildSettlement(-1, 0, TOP);
	player.buildRoad(-1, 0, UP);
	player.buildSettlement(1, 0, BOTTOM);
	player.buildRoad(0, -1, RIGHT);
	player.addResource(LUMBER, 1);
	player.addResource(ORE, 1);
	player.addResource(WOOL, 1);
	player.addDevCard(KNIGHT);
	cout << player.toString() << "\n";

	// only one player is in the game
	vector<Player> onePlayer;
	onePlayer.push_back(player);
	vector<Tile> defaultTiles = createDefaultTiles();
	GameEngine game(onePlayer, defaultTiles);
	game.secondStage();

	// test first stage
	// testFirstStage();

	// Iteration 1 tests
	//iterOneCheck();


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

void iterOneCheck() {
	// create players
	Player player1 = Player("Emil", RED);
	Player player2 = Player("Bram", GREEN);
	Player player3 = Player("Alex", BLUE);
	Player player4 = Player("John", YELLOW);
	array<Player*, 4> players{ &player1, &player2, &player3, &player4 }; // player pointers are in the array

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
	std::array<int, 3> testArray1 = player1.getSettlements()[1].getLoc();
	cout << "testArray: " << testArray1[0] << " " << testArray1[1] << " " << testArray1[2] << "\n\n";

	std::array<int, 3> testArray0 = player1.getSettlements()[0].getLoc();
	cout << "testArray: " << testArray0[0] << " " << testArray0[1] << " " << testArray0[2] << "\n\n";

	// add resources to player 1
	player1.addResource(GRAIN, 1);
	player1.addResource(BRICK, 1);
	player1.addResource(WOOL, 1);
	player1.addResource(LUMBER, 0);
	player1.addResource(ORE, 1);
	cout << player1.toString() << "\n\n";
}

vector<Tile> createDefaultTiles() {
	vector<Tile> defaultTiles;

	// x = 0
	defaultTiles.push_back(Tile(0, 0, DESERT, -1));
	defaultTiles.push_back(Tile(0, 1, MOUNTAINS, 4));
	defaultTiles.push_back(Tile(0, 2, FOREST, 6));
	defaultTiles.push_back(Tile(0, 3, SEA, -1));
	defaultTiles.push_back(Tile(0, -1, FOREST, 3));
	defaultTiles.push_back(Tile(0, -2, HILLS, 11));
	defaultTiles.push_back(Tile(0, -3, SEA, -1));

	// x = 1
	defaultTiles.push_back(Tile(1, 0, MOUNTAINS, 6));
	defaultTiles.push_back(Tile(1, 1, FIELDS, 5));
	defaultTiles.push_back(Tile(1, 2, PASTURE, 3));
	defaultTiles.push_back(Tile(1, 3, SEA, -1));
	defaultTiles.push_back(Tile(1, -1, PASTURE, 12));
	defaultTiles.push_back(Tile(1, -2, SEA, -1));

	// x = 2
	defaultTiles.push_back(Tile(2, 0, FIELDS, 9));
	defaultTiles.push_back(Tile(2, 1, FOREST, 10));
	defaultTiles.push_back(Tile(2, 2, PASTURE, 8));
	defaultTiles.push_back(Tile(2, 3, SEA, -1));
	defaultTiles.push_back(Tile(2, -1, SEA, -1));

	// x = 3
	defaultTiles.push_back(Tile(3, 0, SEA, -1));
	defaultTiles.push_back(Tile(3, 1, SEA, -1));
	defaultTiles.push_back(Tile(3, 2, SEA, -1));
	defaultTiles.push_back(Tile(3, 3, SEA, -1));

	// x = -1
	defaultTiles.push_back(Tile(-1, 0, HILLS, 9));
	defaultTiles.push_back(Tile(-1, 1, FIELDS, 2));
	defaultTiles.push_back(Tile(-1, 2, SEA, -1));
	defaultTiles.push_back(Tile(-1, -1, MOUNTAINS, 11));
	defaultTiles.push_back(Tile(-1, -2, PASTURE, 4));
	defaultTiles.push_back(Tile(-1, -3, SEA, -1));

	// x = -2
	defaultTiles.push_back(Tile(-2, 0, FOREST, 5));
	defaultTiles.push_back(Tile(-2, 1, SEA, -1));
	defaultTiles.push_back(Tile(-2, -1, FIELDS, 10));
	defaultTiles.push_back(Tile(-2, -2, HILLS, 8));
	defaultTiles.push_back(Tile(-2, -3, SEA, -1));

	// x = -3
	defaultTiles.push_back(Tile(-3, 0, SEA, -1));
	defaultTiles.push_back(Tile(-3, -1, SEA, -1));
	defaultTiles.push_back(Tile(-3, -2, SEA, -1));
	defaultTiles.push_back(Tile(-3, -3, SEA, -1));

	return defaultTiles;
}

vector<Player> createDefaultPlayers() {
	vector<Player> defaultPlayers;
	defaultPlayers.push_back(Player("Alexanderr", RED));
	defaultPlayers.push_back(Player("Lin", GREEN));
	defaultPlayers.push_back(Player("Jean", BLUE));
	defaultPlayers.push_back(Player("Marianne", YELLOW));

	return defaultPlayers;
}

void testFirstStage() {
	// Default tiles
	vector<Tile> defaultTiles = createDefaultTiles();
	vector<Player> defaultPlayers = createDefaultPlayers();

	// only one player (for testing)
	vector<Player> onePlayer;
	onePlayer.push_back(Player("Alex", RED));
	GameEngine game(onePlayer, defaultTiles);
	game.firstStage();
	game.printInfoPlayers();
}

