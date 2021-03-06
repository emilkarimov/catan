/// \file
/// Main.cpp

#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <map>
#include <iostream>
#include <math.h>

#include "Building.h"
#include "City.h"
#include "Settlement.h"
#include "Road.h"
#include "Enums.h"
#include "Player.h"
#include "Tile.h"
#include "Robber.h"
#include "GameEngine.h"
//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
using namespace std;

// test functions declarations
void iterOneCheck();
void testFirstStage();
void testSecondStage();
void testSecondStage2();
void testSecondStage3();
void testFindCorners();
void testDestributeResources();
void testRollDice();
void testGame();
void testSDL1();
void testSDL2();
void testSDL3();
void testSDL4();
void testSDL5();

// 37 default tiles
vector<Tile> createDefaultTiles();
// 4 default players
vector<Player> createDefaultPlayers();

int main(int argc, char* args[])
{
	// Let's keep the main clean. If you want to do some tests with your code, you can just create
	// a function and call it from here like it is done below:

	// Iteration 1 tests
	//iterOneCheck();

	// test first stage
	//testFirstStage();

	// test second stage
	//testSecondStage();

	// test second stage2
	//testSecondStage2();

	// test findCorners
	//testFindCorners();

	// test distribution of resources
	//testDestributeResources();

	// test roll dice
	// testRollDice();

	// SDL experiments
	//testSDL5();

	// test full game (demo)
	testSecondStage3();

	// test full game
	//testGame();
	return 0;
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

void testSecondStage() {
	// player initialisation
	Player player = Player("Alex", RED);
	player.buildSettlement(-1, 0, TOP);
	player.buildRoad(-1, 0, UP);
	player.buildSettlement(1, 0, BOTTOM);
	player.buildRoad(0, -1, RIGHT);
	player.addResource(LUMBER, 5);
	player.addResource(ORE, 5);
	player.addResource(WOOL, 5);
	player.addResource(BRICK, 5);
	player.addResource(GRAIN, 5);
	player.addDevCard(KNIGHT);
	player.addDevCard(ROADBUILDING);
	player.addDevCard(YEAROFPLENTY);
	player.addDevCard(MONOPOLY);
	cout << player.toString() << "\n";

	// only one player is in the game
	vector<Player> onePlayer;
	onePlayer.push_back(player);
	vector<Tile> defaultTiles = createDefaultTiles();
	Board board = Board(defaultTiles);
	GameEngine game(onePlayer, board);
	game.secondStage();
}

void testFindCorners() {
	// Default tiles
	vector<Tile> defaultTiles = createDefaultTiles();

	// only one player (for testing)
	vector<Player> onePlayer;
	onePlayer.push_back(Player("Alex", RED));
	Board board = Board(defaultTiles);
	GameEngine game(onePlayer, board);
	game.printInfoPlayers();

	std::vector<std::array<int, 3>> corners;
	corners = board.findCornersAtDiceNum(2);
	for (auto corner : corners) {
		cout << corner[0] << " " << corner[1] << " " << corner[2] << "\n";
	}
}

void testDestributeResources() {
	// player initialisation
	Player player1 = Player("Alex", RED);
	player1.buildSettlement(-1, 0, TOP);
	player1.buildRoad(-1, 0, UP);
	player1.buildSettlement(1, 0, BOTTOM);
	player1.buildRoad(0, -1, RIGHT);

	// player initialisation
	Player player2 = Player("Emil", GREEN);
	player2.buildSettlement(0, -2, TOP);
	player2.buildSettlement(0, 2, BOTTOM);

	// two players in the game
	vector<Player> players;
	players.push_back(player1);
	players.push_back(player2);
	vector<Tile> defaultTiles = createDefaultTiles();
	Board board = Board(defaultTiles);
	GameEngine game(players, board);
	game.distributeResources(2);
	game.printInfoPlayers();
	game.distributeResources(4);
	game.printInfoPlayers();
	game.distributeResources(9);
	game.printInfoPlayers();
	game.distributeResources(3);
	game.printInfoPlayers();
	game.distributeResources(6);
	game.printInfoPlayers();
	game.distributeResources(12);
	game.printInfoPlayers();
}

void testRollDice() {
	// Default tiles
	vector<Tile> defaultTiles = createDefaultTiles();

	// only one player (for testing)
	vector<Player> onePlayer;
	onePlayer.push_back(Player("Alex", RED));
	Board board = Board(defaultTiles);
	GameEngine game(onePlayer, board);
	game.printInfoPlayers();

	cout << game.rollDice() << "\n";
}

void testSecondStage2() {
	// player initialisation
	Player player1 = Player("Dave", RED);
	player1.buildSettlement(-1, 0, TOP);
	player1.buildRoad(-1, 0, UP);
	player1.buildSettlement(1, 0, BOTTOM);
	player1.buildRoad(0, -1, RIGHT);
	player1.addResource(LUMBER, 5);
	player1.addResource(ORE, 5);
	player1.addResource(WOOL, 5);
	player1.addResource(BRICK, 5);
	player1.addResource(GRAIN, 5);
	player1.addDevCard(KNIGHT);
	player1.addDevCard(ROADBUILDING);
	player1.addDevCard(YEAROFPLENTY);
	player1.addDevCard(MONOPOLY);
	cout << player1.toString() << "\n\n";

	Player player2 = Player("Emil", BLUE);
	player2.buildSettlement(0, 1, TOP);
	player2.buildRoad(0, 1, UP);
	player2.buildSettlement(2, 2, BOTTOM);
	player2.buildRoad(1, 1, RIGHT);
	player2.addResource(LUMBER, 5);
	player2.addResource(ORE, 5);
	player2.addResource(WOOL, 5);
	player2.addResource(BRICK, 5);
	player2.addResource(GRAIN, 5);
	player2.addDevCard(KNIGHT);
	player2.addDevCard(ROADBUILDING);
	player2.addDevCard(YEAROFPLENTY);
	player2.addDevCard(MONOPOLY);
	cout << player2.toString() << "\n\n";

	Player player3 = Player("Bram", YELLOW);
	player3.buildSettlement(2, 1, BOTTOM);
	player3.buildRoad(1, 0, RIGHT);
	player3.buildSettlement(-1, -1, BOTTOM);
	player3.buildRoad(-1, -1, DOWN);
	player3.addResource(LUMBER, 5);
	player3.addResource(ORE, 5);
	player3.addResource(WOOL, 5);
	player3.addResource(BRICK, 5);
	player3.addResource(GRAIN, 5);
	player3.addDevCard(KNIGHT);
	player3.addDevCard(ROADBUILDING);
	player3.addDevCard(YEAROFPLENTY);
	player3.addDevCard(MONOPOLY);
	cout << player3.toString() << "\n\n";

	Player player4 = Player("Alex", GREEN);
	player4.buildSettlement(1, 1, BOTTOM);
	player4.buildRoad(0, 0, UP);
	player4.buildSettlement(-2, -1, TOP);
	player4.buildRoad(-2, -1, UP);
	player4.addResource(LUMBER, 5);
	player4.addResource(ORE, 5);
	player4.addResource(WOOL, 5);
	player4.addResource(BRICK, 5);
	player4.addResource(GRAIN, 5);
	player4.addDevCard(KNIGHT);
	player4.addDevCard(ROADBUILDING);
	player4.addDevCard(YEAROFPLENTY);
	player4.addDevCard(MONOPOLY);
	cout << player4.toString() << "\n\n";

	// vector of players
	vector<Player> players;
	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);
	players.push_back(player4);
	vector<Tile> defaultTiles = createDefaultTiles();
	Board board = Board(defaultTiles);
	GameEngine game(players, board);
	game.secondStage();
}

void testSecondStage3() {
	// player initialisation
	Player player1 = Player("Dave (red)", RED);
	player1.buildSettlement(-1, 0, TOP);
	player1.buildRoad(-1, 0, UP);
	player1.buildSettlement(1, 0, BOTTOM);
	player1.buildRoad(0, -1, RIGHT);
	player1.addResource(LUMBER, 1);
	player1.addResource(ORE, 1);
	player1.addResource(WOOL, 1);
	
	Player player2 = Player("Emil (blue)", BLUE);
	player2.buildSettlement(0, 1, TOP);
	player2.buildRoad(0, 1, UP);
	player2.buildSettlement(2, 2, BOTTOM);
	player2.buildRoad(1, 1, RIGHT);
	player2.addResource(LUMBER, 1);
	player2.addResource(GRAIN, 1);
	player2.addResource(WOOL, 1);

	Player player3 = Player("Bram (yellow)", YELLOW);
	player3.buildSettlement(2, 1, BOTTOM);
	player3.buildRoad(1, 0, RIGHT);
	player3.buildSettlement(-1, -1, BOTTOM);
	player3.buildRoad(-1, -1, DOWN);
	player3.addResource(ORE, 1);
	player3.addResource(WOOL, 1);
	player3.addResource(BRICK, 1);
	
	Player player4 = Player("Alex (green)", GREEN);
	player4.buildSettlement(1, 1, BOTTOM);
	player4.buildRoad(0, 0, UP);
	player4.buildSettlement(-2, -1, TOP);
	player4.buildRoad(-2, -1, UP);
	player4.addResource(LUMBER, 1);
	player4.addResource(BRICK, 1);
	player4.addResource(GRAIN, 1);

	// vector of players
	vector<Player> players;
	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);
	players.push_back(player4);
	vector<Tile> defaultTiles = createDefaultTiles();
	Board board = Board(defaultTiles);
	GameEngine game(players, board);
	game.printInfoPlayers();
	game.secondStage();
}

void testGame() {
	// player initialisation
	Player player1 = Player("Dave", RED);
	Player player2 = Player("Emil", BLUE);
	Player player3 = Player("Bram", YELLOW);
	Player player4 = Player("Alex", GREEN);
	
	// vector of players
	vector<Player> players;
	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);
	players.push_back(player4);
	vector<Tile> defaultTiles = createDefaultTiles();
	Board board = Board(defaultTiles);
	GameEngine game(players, board);
	game.start();
}