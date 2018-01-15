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
#include "CornerCoord.h"
//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
using namespace std;

void rollDice();
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
vector<Tile> createDefaultTiles();
vector<Player> createDefaultPlayers();

void drawHex(SDL_Renderer* renderer, std::array<int, 2> CENTER, int RADIUS, Terrain type);
void drawLine(SDL_Renderer* renderer, int start_x, int start_y, int end_x, int end_y, std::array<int, 3> color);
void drawTile(SDL_Renderer* renderer, Tile& tile);
void drawRoad(SDL_Renderer* renderer, Road& road);
void drawSettlement(SDL_Renderer* renderer, Settlement& settlement);
void drawCity(SDL_Renderer* renderer, City& city);
void drawRobber(SDL_Renderer* renderer, Robber& robber);

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

	// test full game
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

//////// SDL /////////

void testSDL1() {
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);

			//Fill the surface white
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x77, 0x77, 0x77));

			//Update the surface
			SDL_UpdateWindowSurface(window);

			//Wait two seconds
			SDL_Delay(2000);
		}
	}

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();
}

void testSDL2() {
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;

		if (SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) == 0) {
			SDL_bool done = SDL_FALSE;

			while (!done) {
				SDL_Event event;

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);

				SDL_SetRenderDrawColor(renderer, 0, 191, 255, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawLine(renderer, 0, 300, 799, 300);
				SDL_RenderPresent(renderer);

				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						done = SDL_TRUE;
					}
				}
			}
		}

		if (renderer) {
			SDL_DestroyRenderer(renderer);
		}
		if (window) {
			SDL_DestroyWindow(window);
		}
	}
	SDL_Quit();
}

void testSDL3() {
    #define POINTS_COUNT 4

	static SDL_Point points[POINTS_COUNT] = {
		{ 320, 200 },
		{ 300, 240 },
		{ 340, 240 },
		{ 320, 200 }
	};

	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;

		if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) == 0) {
			SDL_bool done = SDL_FALSE;

			while (!done) {
				SDL_Event event;

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);

				SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawLines(renderer, points, POINTS_COUNT);
				SDL_RenderPresent(renderer);

				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						done = SDL_TRUE;
					}
				}
			}
		}

		if (renderer) {
			SDL_DestroyRenderer(renderer);
		}
		if (window) {
			SDL_DestroyWindow(window);
		}
	}
	SDL_Quit();
}


void testSDL4() {
	int WIDTH{ 800 };
	int HEIGHT{ 600 };
	std::array<int, 2> CENTER{ WIDTH / 2, HEIGHT / 2 };
	int RADIUS{ 40 };
	int RADCOS{ static_cast<int>(round(RADIUS*sqrt(3) / 2)) };
	std::cout << RADCOS << "\n";

	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;

		if (SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) == 0) {
			SDL_bool done = SDL_FALSE;

			while (!done) {
				SDL_Event event;

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);

				SDL_SetRenderDrawColor(renderer, 0, 191, 255, SDL_ALPHA_OPAQUE);
				
				// 0 row
				drawHex(renderer, { CENTER[0], CENTER[1] }, RADIUS, DESERT);
				drawLine(renderer, CENTER[0], CENTER[1] - RADIUS - 1, CENTER[0] + RADCOS + 1, CENTER[1] - RADIUS / 2 - 1, { 255,0,255 });
				drawLine(renderer, CENTER[0], CENTER[1] - RADIUS - 2, CENTER[0] + RADCOS + 1, CENTER[1] - RADIUS / 2 - 2, { 255,0,255 });
				drawLine(renderer, CENTER[0], CENTER[1] - RADIUS, CENTER[0] + RADCOS + 1, CENTER[1] - RADIUS / 2 , { 255,0,255 });

				drawHex(renderer, { CENTER[0] + 2* RADCOS+2, CENTER[1] }, RADIUS, MOUNTAINS);
				drawHex(renderer, { CENTER[0] + 4 * RADCOS + 4, CENTER[1] }, RADIUS, FIELDS);
				drawHex(renderer, { CENTER[0] + 6 * RADCOS + 6, CENTER[1] }, RADIUS, SEA);

				drawHex(renderer, { CENTER[0] - 2 * RADCOS - 2, CENTER[1] }, RADIUS, HILLS);
				drawHex(renderer, { CENTER[0] - 4 * RADCOS - 4, CENTER[1] }, RADIUS, FOREST);
				drawHex(renderer, { CENTER[0] - 6 * RADCOS - 6, CENTER[1] }, RADIUS, SEA);

				// 1 row up
				drawHex(renderer, { CENTER[0]-RADCOS-1, CENTER[1]-RADIUS/2-RADIUS-2 }, RADIUS, MOUNTAINS);
				drawHex(renderer, { CENTER[0] - RADCOS - 1 + 2 * RADCOS + 2, CENTER[1] - RADIUS / 2 - RADIUS - 2 }, RADIUS, FIELDS );
				drawHex(renderer, { CENTER[0] - RADCOS - 1 + 4 * RADCOS + 4, CENTER[1] - RADIUS / 2 - RADIUS - 2 }, RADIUS, FOREST);
				drawHex(renderer, { CENTER[0] - RADCOS - 1 + 6 * RADCOS + 6, CENTER[1] - RADIUS / 2 - RADIUS - 2 }, RADIUS, SEA);
				drawHex(renderer, { CENTER[0] - RADCOS - 1 - 2 * RADCOS - 2, CENTER[1] - RADIUS / 2 - RADIUS - 2 }, RADIUS, FIELDS);
				drawHex(renderer, { CENTER[0] - RADCOS - 1 - 4 * RADCOS - 4, CENTER[1] - RADIUS / 2 - RADIUS - 2 }, RADIUS, SEA);

				// 1 row down
				drawHex(renderer, { CENTER[0] - RADCOS - 1, CENTER[1] + RADIUS / 2 + RADIUS + 2 }, RADIUS, MOUNTAINS);
				drawHex(renderer, { CENTER[0] - RADCOS - 1 + 2 * RADCOS + 2, CENTER[1] + RADIUS / 2 + RADIUS + 2 }, RADIUS, FOREST);
				drawHex(renderer, { CENTER[0] - RADCOS - 1 + 4 * RADCOS + 4, CENTER[1] + RADIUS / 2 + RADIUS + 2 }, RADIUS, PASTURE);
				drawHex(renderer, { CENTER[0] - RADCOS - 1 + 6 * RADCOS + 6, CENTER[1] + RADIUS / 2 + RADIUS + 2 }, RADIUS, SEA);
				drawHex(renderer, { CENTER[0] - RADCOS - 1 - 2 * RADCOS - 2, CENTER[1] + RADIUS / 2 + RADIUS + 2 }, RADIUS, FIELDS);
				drawHex(renderer, { CENTER[0] - RADCOS - 1 - 4 * RADCOS - 4, CENTER[1] + RADIUS / 2 + RADIUS + 2 }, RADIUS, SEA);

				// 2 rows up
				drawHex(renderer, { CENTER[0], CENTER[1] - 2*(RADIUS / 2 + RADIUS + 2) }, RADIUS, PASTURE);
				drawHex(renderer, { CENTER[0] + 2 * RADCOS + 2, CENTER[1] - 2 * (RADIUS / 2 + RADIUS + 2) }, RADIUS, PASTURE);
				drawHex(renderer, { CENTER[0] + 4 * RADCOS + 4, CENTER[1] - 2 * (RADIUS / 2 + RADIUS + 2) }, RADIUS, SEA);
				drawHex(renderer, { CENTER[0] - 2 * RADCOS - 2, CENTER[1] - 2 * (RADIUS / 2 + RADIUS + 2) }, RADIUS, FOREST);
				drawHex(renderer, { CENTER[0] - 4 * RADCOS - 4, CENTER[1] - 2 * (RADIUS / 2 + RADIUS + 2) }, RADIUS, SEA);

				// 2 rows down
				drawHex(renderer, { CENTER[0], CENTER[1] + 2 * (RADIUS / 2 + RADIUS + 2) }, RADIUS, PASTURE);
				drawHex(renderer, { CENTER[0] + 2 * RADCOS + 2, CENTER[1] + 2 * (RADIUS / 2 + RADIUS + 2) }, RADIUS, HILLS);
				drawHex(renderer, { CENTER[0] + 4 * RADCOS + 4, CENTER[1] + 2 * (RADIUS / 2 + RADIUS + 2) }, RADIUS, SEA);
				drawHex(renderer, { CENTER[0] - 2 * RADCOS - 2, CENTER[1] + 2 * (RADIUS / 2 + RADIUS + 2) }, RADIUS, HILLS);
				drawHex(renderer, { CENTER[0] - 4 * RADCOS - 4, CENTER[1] + 2 * (RADIUS / 2 + RADIUS + 2) }, RADIUS, SEA);

				// 3 rows up
				drawHex(renderer, { CENTER[0] - RADCOS - 1, CENTER[1] - 3 * (RADIUS / 2 + RADIUS + 2) }, RADIUS, SEA);
				drawHex(renderer, { CENTER[0] - RADCOS - 1 + 2 * RADCOS + 2, CENTER[1] - 3 * (RADIUS / 2 + RADIUS + 2) }, RADIUS, SEA);
				drawHex(renderer, { CENTER[0] - RADCOS - 1 + 4 * RADCOS + 4, CENTER[1] - 3 * (RADIUS / 2 + RADIUS + 2) }, RADIUS, SEA);
				drawHex(renderer, { CENTER[0] - RADCOS - 1 - 2 * RADCOS - 2, CENTER[1] - 3 * (RADIUS / 2 + RADIUS + 2) }, RADIUS, SEA);

				// 3 rows down
				drawHex(renderer, { CENTER[0] - RADCOS - 1, CENTER[1] + 3 * (RADIUS / 2 + RADIUS + 2) }, RADIUS, SEA);
				drawHex(renderer, { CENTER[0] - RADCOS - 1 + 2 * RADCOS + 2, CENTER[1] + 3 * (RADIUS / 2 + RADIUS + 2) }, RADIUS, SEA);
				drawHex(renderer, { CENTER[0] - RADCOS - 1 + 4 * RADCOS + 4, CENTER[1] + 3 * (RADIUS / 2 + RADIUS + 2) }, RADIUS, SEA);
				drawHex(renderer, { CENTER[0] - RADCOS - 1 - 2 * RADCOS - 2, CENTER[1] + 3 * (RADIUS / 2 + RADIUS + 2) }, RADIUS, SEA);

				// rectangle
				SDL_Rect srcrect;
				srcrect.x = CENTER[0] - 7;
				srcrect.y = CENTER[1] - RADIUS - 1 - 7;
				srcrect.w = 14;
				srcrect.h = 14;
				const SDL_Rect* rectPtr{ &srcrect };
				SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawRect(renderer, rectPtr);
				// fill in

				SDL_RenderFillRect(renderer, rectPtr);

				// robber
				int rob_x{ CENTER[0] - 27 };
				int rob_y{ CENTER[1]};
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawLine(renderer, rob_x, rob_y, rob_x + 4, rob_y + 4);
				SDL_RenderDrawLine(renderer, rob_x, rob_y, rob_x - 4, rob_y - 4);
				SDL_RenderDrawLine(renderer, rob_x, rob_y, rob_x - 4, rob_y + 4);
				SDL_RenderDrawLine(renderer, rob_x, rob_y, rob_x + 4, rob_y - 4);

				SDL_RenderPresent(renderer);

				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						done = SDL_TRUE;
					}
				}
			}
		}

		if (renderer) {
			SDL_DestroyRenderer(renderer);
		}
		if (window) {
			SDL_DestroyWindow(window);
		}
	}
	SDL_Quit();
}


void testSDL5() {
	int WIDTH{ 800 };
	int HEIGHT{ 600 };
	std::array<int, 2> CENTER{ WIDTH / 2, HEIGHT / 2 };
	int RADIUS{ 40 };
	int RADCOS{ static_cast<int>(round(RADIUS*sqrt(3) / 2)) };
	std::cout << RADCOS << "\n";

	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;

		if (SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) == 0) {
			SDL_bool done = SDL_FALSE;

			while (!done) {
				SDL_Event event;

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);

				SDL_SetRenderDrawColor(renderer, 0, 191, 255, SDL_ALPHA_OPAQUE);

				// draw tiles
				vector<Tile> defaultTiles = createDefaultTiles();
				for (Tile& tile : defaultTiles) {
					drawTile(renderer, tile);
				}

				// draw roads
				Road road1{ Road(1, 1, UP) };
				drawRoad(renderer, road1);
				Road road2{ Road(0, 0, RIGHT) };
				drawRoad(renderer, road2);
				Road road3{ Road(-1, -1, DOWN) };
				drawRoad(renderer, road3);

				// draw settlements
				Settlement s1{ Settlement(0, -1, TOP) };
				drawSettlement(renderer, s1);
				Settlement s2{ Settlement(1, 1, TOP) };
				drawSettlement(renderer, s2);
				Settlement s3{ Settlement(-1, -1, BOTTOM) };
				drawSettlement(renderer, s3);

				// draw cities
				City c1{ City(0, -1, TOP) };
				drawCity(renderer, c1);

				// draw robber
				Robber robber1{ Robber(0, 0) };
				drawRobber(renderer, robber1);
				Robber robber2{ Robber(2, 1) };
				drawRobber(renderer, robber2);
				Robber robber3{ Robber(-2, -1) };
				drawRobber(renderer, robber3);

			
				SDL_RenderPresent(renderer);

				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						done = SDL_TRUE;
					}
				}
			}
		}

		if (renderer) {
			SDL_DestroyRenderer(renderer);
		}
		if (window) {
			SDL_DestroyWindow(window);
		}
	}
	SDL_Quit();
}


void drawHex(SDL_Renderer* renderer, std::array<int,2> CENTER, int RADIUS, Terrain type) {
	int R;
	int G;
	int B;
	switch (type) {
	case FIELDS:
		R = 252;
		G = 136;
		B = 20;
		break;
	case DESERT:
		R = 245;
		G = 201;
		B = 89;
		break;
	case HILLS:
		R = 128;
		G = 44;
		B = 2;
		break;
	case PASTURE:
		R = 110;
		G = 190;
		B = 29;
		break;
	case FOREST:
		R = 1;
		G = 74;
		B = 31;
		break;
	case MOUNTAINS:
		R = 93;
		G = 93;
		B = 93;
		break;
	case SEA:
		R = 0;
		G = 191;
		B = 255;
		break;
	default:
		R = 255;
		G = 255;
		B = 255;
		break;
	}

	SDL_SetRenderDrawColor(renderer, R, G, B, SDL_ALPHA_OPAQUE);

	int RADCOS{ static_cast<int>(round(RADIUS*sqrt(3) / 2)) };
	SDL_RenderDrawLine(renderer, CENTER[0], CENTER[1] - RADIUS, CENTER[0] + RADCOS, CENTER[1] - RADIUS / 2);
	SDL_RenderDrawLine(renderer, CENTER[0], CENTER[1] - RADIUS, CENTER[0] - RADCOS, CENTER[1] - RADIUS / 2);
	SDL_RenderDrawLine(renderer, CENTER[0] + RADCOS, CENTER[1] - RADIUS / 2, CENTER[0] + RADCOS, CENTER[1] + RADIUS / 2);
	SDL_RenderDrawLine(renderer, CENTER[0] - RADCOS, CENTER[1] - RADIUS / 2, CENTER[0] - RADCOS, CENTER[1] + RADIUS / 2);
	SDL_RenderDrawLine(renderer, CENTER[0] + RADCOS, CENTER[1] + RADIUS / 2, CENTER[0], CENTER[1] + RADIUS);
	SDL_RenderDrawLine(renderer, CENTER[0] - RADCOS, CENTER[1] + RADIUS / 2, CENTER[0], CENTER[1] + RADIUS);

	for (int i{ 40 }; i > 0; i--) {
		int RADCOS{ static_cast<int>(round(i*sqrt(3) / 2)) };
		RADIUS = i;
		SDL_RenderDrawLine(renderer, CENTER[0], CENTER[1] - RADIUS, CENTER[0] + RADCOS, CENTER[1] - RADIUS / 2);
		SDL_RenderDrawLine(renderer, CENTER[0], CENTER[1] - RADIUS, CENTER[0] - RADCOS, CENTER[1] - RADIUS / 2);
		SDL_RenderDrawLine(renderer, CENTER[0] + RADCOS, CENTER[1] - RADIUS / 2, CENTER[0] + RADCOS, CENTER[1] + RADIUS / 2);
		SDL_RenderDrawLine(renderer, CENTER[0] - RADCOS, CENTER[1] - RADIUS / 2, CENTER[0] - RADCOS, CENTER[1] + RADIUS / 2);
		SDL_RenderDrawLine(renderer, CENTER[0] + RADCOS, CENTER[1] + RADIUS / 2, CENTER[0], CENTER[1] + RADIUS);
		SDL_RenderDrawLine(renderer, CENTER[0] - RADCOS, CENTER[1] + RADIUS / 2, CENTER[0], CENTER[1] + RADIUS);
	}
	for (int i{ 40 }; i > 0; i--) {
		int RADCOS{ static_cast<int>(floor(i*sqrt(3) / 2)) };
		RADIUS = i;
		SDL_RenderDrawLine(renderer, CENTER[0], CENTER[1] - RADIUS, CENTER[0] + RADCOS, CENTER[1] - RADIUS / 2);
		SDL_RenderDrawLine(renderer, CENTER[0], CENTER[1] - RADIUS, CENTER[0] - RADCOS, CENTER[1] - RADIUS / 2);
		SDL_RenderDrawLine(renderer, CENTER[0] + RADCOS, CENTER[1] - RADIUS / 2, CENTER[0] + RADCOS, CENTER[1] + RADIUS / 2);
		SDL_RenderDrawLine(renderer, CENTER[0] - RADCOS, CENTER[1] - RADIUS / 2, CENTER[0] - RADCOS, CENTER[1] + RADIUS / 2);
		SDL_RenderDrawLine(renderer, CENTER[0] + RADCOS, CENTER[1] + RADIUS / 2, CENTER[0], CENTER[1] + RADIUS);
		SDL_RenderDrawLine(renderer, CENTER[0] - RADCOS, CENTER[1] + RADIUS / 2, CENTER[0], CENTER[1] + RADIUS);
	}
	for (int i{ 39 }; i > 0; i--) {
		int RADCOS{ static_cast<int>(ceil(i*sqrt(3) / 2)) };
		RADIUS = i;
		SDL_RenderDrawLine(renderer, CENTER[0], CENTER[1] - RADIUS, CENTER[0] + RADCOS, CENTER[1] - RADIUS / 2);
		SDL_RenderDrawLine(renderer, CENTER[0], CENTER[1] - RADIUS, CENTER[0] - RADCOS, CENTER[1] - RADIUS / 2);
		SDL_RenderDrawLine(renderer, CENTER[0] + RADCOS, CENTER[1] - RADIUS / 2, CENTER[0] + RADCOS, CENTER[1] + RADIUS / 2);
		SDL_RenderDrawLine(renderer, CENTER[0] - RADCOS, CENTER[1] - RADIUS / 2, CENTER[0] - RADCOS, CENTER[1] + RADIUS / 2);
		SDL_RenderDrawLine(renderer, CENTER[0] + RADCOS, CENTER[1] + RADIUS / 2, CENTER[0], CENTER[1] + RADIUS);
		SDL_RenderDrawLine(renderer, CENTER[0] - RADCOS, CENTER[1] + RADIUS / 2, CENTER[0], CENTER[1] + RADIUS);
	}
}

void drawLine(SDL_Renderer* renderer, int start_x, int start_y, int end_x, int end_y, std::array<int, 3> color) {
	SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, start_x, start_y, end_x, end_y);
}


void drawTile(SDL_Renderer* renderer, Tile& tile) {
	int WIDTH{ 800 };
	int HEIGHT{ 600 };
	std::array<int, 2> CENTER{ WIDTH / 2, HEIGHT / 2 };
	int RADIUS{ 40 };
	int RADCOS{ static_cast<int>(round(RADIUS*sqrt(3) / 2)) };

	std::array<int, 2> tileCoord{ tile.getCoord() };
	int x{ CENTER[0] + 2 * tileCoord[0] * (RADCOS + 1) - tileCoord[1] * (RADCOS + 1) };
	int y{ CENTER[1] - tileCoord[1] * (RADIUS + RADIUS / 2 + 2) };


	Terrain type{ tile.getTerrainType() };

	int R;
	int G;
	int B;
	switch (type) {
	case FIELDS:
		R = 252;
		G = 136;
		B = 20;
		break;
	case DESERT:
		R = 245;
		G = 201;
		B = 89;
		break;
	case HILLS:
		R = 128;
		G = 44;
		B = 2;
		break;
	case PASTURE:
		R = 110;
		G = 190;
		B = 29;
		break;
	case FOREST:
		R = 1;
		G = 74;
		B = 31;
		break;
	case MOUNTAINS:
		R = 93;
		G = 93;
		B = 93;
		break;
	case SEA:
		R = 0;
		G = 191;
		B = 255;
		break;
	default:
		R = 255;
		G = 255;
		B = 255;
		break;
	}

	SDL_SetRenderDrawColor(renderer, R, G, B, SDL_ALPHA_OPAQUE);

	SDL_RenderDrawLine(renderer, x, y - RADIUS, x + RADCOS, y - RADIUS / 2);
	SDL_RenderDrawLine(renderer, x, y - RADIUS, x - RADCOS, y - RADIUS / 2);
	SDL_RenderDrawLine(renderer, x + RADCOS, y - RADIUS / 2, x + RADCOS, y + RADIUS / 2);
	SDL_RenderDrawLine(renderer, x - RADCOS, y - RADIUS / 2, x - RADCOS, y + RADIUS / 2);
	SDL_RenderDrawLine(renderer, x + RADCOS, y + RADIUS / 2, x, y + RADIUS);
	SDL_RenderDrawLine(renderer, x - RADCOS, y + RADIUS / 2, x, y + RADIUS);

	for (int i{ 40 }; i > 0; i--) {
		RADCOS = static_cast<int>(round(i*sqrt(3) / 2));
		RADIUS = i;
		SDL_RenderDrawLine(renderer, x, y - RADIUS, x + RADCOS, y - RADIUS / 2);
		SDL_RenderDrawLine(renderer, x, y - RADIUS, x - RADCOS, y - RADIUS / 2);
		SDL_RenderDrawLine(renderer, x + RADCOS, y - RADIUS / 2, x + RADCOS, y + RADIUS / 2);
		SDL_RenderDrawLine(renderer, x - RADCOS, y - RADIUS / 2, x - RADCOS, y + RADIUS / 2);
		SDL_RenderDrawLine(renderer, x + RADCOS, y + RADIUS / 2, x, y + RADIUS);
		SDL_RenderDrawLine(renderer, x - RADCOS, y + RADIUS / 2, x, y + RADIUS);
	}
	for (int i{ 40 }; i > 0; i--) {
		RADCOS = static_cast<int>(floor(i*sqrt(3) / 2));
		RADIUS = i;
		SDL_RenderDrawLine(renderer, x, y - RADIUS, x + RADCOS, y - RADIUS / 2);
		SDL_RenderDrawLine(renderer, x, y - RADIUS, x - RADCOS, y - RADIUS / 2);
		SDL_RenderDrawLine(renderer, x + RADCOS, y - RADIUS / 2, x + RADCOS, y + RADIUS / 2);
		SDL_RenderDrawLine(renderer, x - RADCOS, y - RADIUS / 2, x - RADCOS, y + RADIUS / 2);
		SDL_RenderDrawLine(renderer, x + RADCOS, y + RADIUS / 2, x, y + RADIUS);
		SDL_RenderDrawLine(renderer, x - RADCOS, y + RADIUS / 2, x, y + RADIUS);
	}
	for (int i{ 40 }; i > 0; i--) {
		RADCOS = static_cast<int>(ceil(i*sqrt(3) / 2));
		RADIUS = i;
		SDL_RenderDrawLine(renderer, x, y - RADIUS, x + RADCOS, y - RADIUS / 2);
		SDL_RenderDrawLine(renderer, x, y - RADIUS, x - RADCOS, y - RADIUS / 2);
		SDL_RenderDrawLine(renderer, x + RADCOS, y - RADIUS / 2, x + RADCOS, y + RADIUS / 2);
		SDL_RenderDrawLine(renderer, x - RADCOS, y - RADIUS / 2, x - RADCOS, y + RADIUS / 2);
		SDL_RenderDrawLine(renderer, x + RADCOS, y + RADIUS / 2, x, y + RADIUS);
		SDL_RenderDrawLine(renderer, x - RADCOS, y + RADIUS / 2, x, y + RADIUS);
	}
}

void drawRoad(SDL_Renderer* renderer, Road& road) {
	int WIDTH{ 800 };
	int HEIGHT{ 600 };
	std::array<int, 2> CENTER{ WIDTH / 2, HEIGHT / 2 };
	int RADIUS{ 40 };
	int RADCOS{ static_cast<int>(round(RADIUS*sqrt(3) / 2)) };

	std::array<int, 3> roadCoord{ road.getLoc() };
	int x{ CENTER[0] + 2 * roadCoord[0] * (RADCOS + 1) - roadCoord[1] * (RADCOS + 1) };
	int y{ CENTER[1] - roadCoord[1] * (RADIUS + RADIUS / 2 + 2) };

	SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);

	switch (roadCoord[2]) {
	case UP:
		SDL_RenderDrawLine(renderer, x, y - RADIUS, x + RADCOS, y - RADIUS / 2);
		SDL_RenderDrawLine(renderer, x, y - RADIUS - 1, x + RADCOS, y - RADIUS / 2 - 1);
		SDL_RenderDrawLine(renderer, x, y - RADIUS - 2, x + RADCOS, y - RADIUS / 2 - 2);
		break;
	case RIGHT:
		SDL_RenderDrawLine(renderer, x + RADCOS, y - RADIUS / 2, x + RADCOS, y + RADIUS / 2);
		SDL_RenderDrawLine(renderer, x + RADCOS + 1, y - RADIUS / 2, x + RADCOS + 1, y + RADIUS / 2);
		//SDL_RenderDrawLine(renderer, x + RADCOS + 2, y - RADIUS / 2, x + RADCOS + 2, y + RADIUS / 2);
		break;
	case DOWN:
		SDL_RenderDrawLine(renderer, x + RADCOS, y + RADIUS / 2, x, y + RADIUS);
		SDL_RenderDrawLine(renderer, x + RADCOS, y + RADIUS / 2 + 1, x, y + RADIUS + 1);
		SDL_RenderDrawLine(renderer, x + RADCOS, y + RADIUS / 2 + 2, x, y + RADIUS + 2);
		break;
	default:
		std::cout << "smth wrong\n";
		break;
	}
}

void drawSettlement(SDL_Renderer* renderer, Settlement& settlement) {
	int WIDTH{ 800 };
	int HEIGHT{ 600 };
	std::array<int, 2> CENTER{ WIDTH / 2, HEIGHT / 2 };
	int RADIUS{ 40 };
	int RADCOS{ static_cast<int>(round(RADIUS*sqrt(3) / 2)) };

	std::array<int, 3> settlementCoord{ settlement.getLoc() };
	int x{ CENTER[0] + 2 * settlementCoord[0] * (RADCOS + 1) - settlementCoord[1] * (RADCOS + 1) };
	int y{ CENTER[1] - settlementCoord[1] * (RADIUS + RADIUS / 2 + 2) };

	// rectangle
	SDL_Rect srcrect;
	const SDL_Rect* rectPtr{ &srcrect };

	SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);

	switch (settlementCoord[2]) {
	case TOP:
		srcrect.x = x - 7;
		srcrect.y = y - RADIUS - 7;
		srcrect.w = 14;
		srcrect.h = 14;
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(renderer, rectPtr);
		break;
	case BOTTOM:
		srcrect.x = x - 7;
		srcrect.y = y + RADIUS - 7;
		srcrect.w = 14;
		srcrect.h = 14;
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(renderer, rectPtr);
		break;
	default:
		std::cout << "smth wrong\n";
		break;
	}
}

void drawCity(SDL_Renderer* renderer, City& city) {
	int WIDTH{ 800 };
	int HEIGHT{ 600 };
	std::array<int, 2> CENTER{ WIDTH / 2, HEIGHT / 2 };
	int RADIUS{ 40 };
	int RADCOS{ static_cast<int>(round(RADIUS*sqrt(3) / 2)) };

	std::array<int, 3> cityCoord{ city.getLoc() };
	int x{ CENTER[0] + 2 * cityCoord[0] * (RADCOS + 1) - cityCoord[1] * (RADCOS + 1) };
	int y{ CENTER[1] - cityCoord[1] * (RADIUS + RADIUS / 2 + 2) };

	// rectangle
	SDL_Rect srcrect;
	const SDL_Rect* rectPtr{ &srcrect };

	SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);

	switch (cityCoord[2]) {
	case TOP:
		srcrect.x = x - 7;
		srcrect.y = y - RADIUS - 7;
		srcrect.w = 14;
		srcrect.h = 14;
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(renderer, rectPtr);
		SDL_RenderFillRect(renderer, rectPtr);
		break;
	case BOTTOM:
		srcrect.x = x - 7;
		srcrect.y = y + RADIUS - 7;
		srcrect.w = 14;
		srcrect.h = 14;
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(renderer, rectPtr);
		SDL_RenderFillRect(renderer, rectPtr);
		break;
	default:
		std::cout << "smth wrong\n";
		break;
	}
}

void drawRobber(SDL_Renderer* renderer, Robber& robber) {
	int WIDTH{ 800 };
	int HEIGHT{ 600 };
	std::array<int, 2> CENTER{ WIDTH / 2, HEIGHT / 2 };
	int RADIUS{ 40 };
	int RADCOS{ static_cast<int>(round(RADIUS*sqrt(3) / 2)) };

	std::array<int, 2> robberCoord{ robber.getLoc() };
	int x{ CENTER[0] + 2 * robberCoord[0] * (RADCOS + 1) - robberCoord[1] * (RADCOS + 1) };
	int y{ CENTER[1] - robberCoord[1] * (RADIUS + RADIUS / 2 + 2) };

	// robber
	int rob_x{ x - 27 };
	int rob_y{ y };
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, rob_x, rob_y, rob_x + 4, rob_y + 4);
	SDL_RenderDrawLine(renderer, rob_x, rob_y, rob_x - 4, rob_y - 4);
	SDL_RenderDrawLine(renderer, rob_x, rob_y, rob_x - 4, rob_y + 4);
	SDL_RenderDrawLine(renderer, rob_x, rob_y, rob_x + 4, rob_y - 4);

}