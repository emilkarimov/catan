/// \file
/// GameEngine.cpp
/// GameEngine class member-function definitions.

#include "GameEngine.h" // Robber class definition
#include <iostream>
#include <string>
#include <stdlib.h> // contains prototypes for functions srand and rand
#include <ctime>

//Using SDL and standard IO
//#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

using namespace std;

// number of resources distributed for settlements and cities
unsigned int NUMRESSET{ 1 };
unsigned int NUMRESCITY{ 1 };
unsigned int VICTORYNUM{ 10 }; // points needed to win

///// SDL //////
int WIDTH{ 800 };
int HEIGHT{ 600 };
std::array<int, 2> CENTER{ WIDTH / 2, HEIGHT / 2 };
int RADIUS{ 40 };
int RADCOS{ static_cast<int>(round(RADIUS*sqrt(3) / 2)) };
///// SDL //////

// constructor 
GameEngine::GameEngine(std::vector<Player> players, Board board)
	: players(players), board(board), robber(0, 0) {
	deck.initDeck();
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);
	SDL_SetWindowPosition(window, 500, 75);
}

// start game
void GameEngine::start() {
	firstStage();
	secondStage();
}

// checks if a corner is available for placing a settlement
bool GameEngine::cornerFree(int x, int y, TileIntersection intersec) {
	std::array<std::array<int, 3>, 3> corners;
	corners = board.getAdjacentCorners(x, y, intersec);
	// check adjacent corners
	for (unsigned int i{ 0 }; i < 3; ++i) {
		for (Player& player : players) {
			if (player.hasPropertyAtCoord(corners[i][0], corners[i][1], corners[i][2])) {
				return false;
			}
		}
	}

	// check intended corner 
	for (Player& player : players) {
		if (player.hasPropertyAtCoord(x, y, intersec)) {
			return false;
		}
	}

	return true;
}

// checks if a road is available for placing a new road
bool GameEngine::roadAvailable(int x, int y, TileEdge edge) {
	// check if each player has a road at this coord 
    for (Player& player : players) {
		if (player.hasRoadAtCoord(x, y, edge)) {
			return false;
		}
	}

	return true;
}

// 1st stage - players build two settlements and two roads
void GameEngine::firstStage() {
	drawUpdate();
	// first settlement and road
	for (unsigned int i{ 0 }; i < players.size(); ++i) {
		// settlement
		handleBuildSettlement(players[i]);

		// road
		handleBuildRoad(players[i]);
	}
	// second settlement and road
	for (int i{ static_cast<int>(players.size()) - 1 }; i > -1; --i) {
		// settlement
		handleBuildSettlement(players[i]);
		addInitResources(players[i]); // add initial resources 

		// road
		handleBuildRoad(players[i]);
	}
}


// 2nd stage - players take actions in turn
void GameEngine::secondStage() {
	drawUpdate();
	bool gameOver{ false };
	while (!gameOver) {
		for (Player& player : players) {
			TurnStage stage = START; // stage of the turn
			std::string moveInput; // input from user
			cout << "\n" << player.getName() + ", what is your move? \noptions:\n";
			cout << possibleMoves(player, stage);

			// handle initial move (roll or play dev card)
			bool NotLegalMove{ true };
			while (NotLegalMove) {
				cin >> moveInput;
				if (moveInput == "1") {
					cout << "roll dice" << "\n";
					handleRollDice(player);
					NotLegalMove = false;
				}
				else if (moveInput == "2" && player.canPlayDev()) {
					cout << "Play development card" << "\n";
					playDevCard(player);
					NotLegalMove = false;
				}
				else {
					cout << "Illegal move. Choose a valid move from the options above" << "\n";
				}
			}

			// roll the dice if the first move was to play dev card
			if (moveInput != "1") {
				cout << "\n" << player.getName() + ", what is your move? \noptions:\n"
					<< "1 - roll dice\n";
				bool NotLegalMove{ true };
				while (NotLegalMove) {
					cin >> moveInput;
					if (moveInput == "1") {
						cout << "roll dice" << "\n";
						handleRollDice(player);
						NotLegalMove = false;
					}
					else {
						cout << "Illegal move. Choose a valid move from the options above" << "\n";
					}
				}
			}

			stage = ROLLED; // dice was rolled

			// next moves
			bool endOfTurn{ false };
			while (!endOfTurn) {
				cout << "\n" << player.getName() + ", what is your move? \noptions:\n";
				cout << possibleMoves(player, stage);
				bool NotLegalMove{ true };
				while (NotLegalMove) {
					cin >> moveInput;
					if (moveInput == "2" && player.canPlayDev()) {
						cout << "Play development card" << "\n";
						playDevCard(player);
						NotLegalMove = false;
					}
					else if (moveInput == "3" && player.canBuildSettlement()) {
						cout << "build settlement" << "\n";
						handleBuildSettlement(player);
						player.removeResource(LUMBER, 1);
						player.removeResource(BRICK, 1);
						player.removeResource(GRAIN, 1);
						player.removeResource(WOOL, 1);
						NotLegalMove = false;
					}
					else if (moveInput == "4" && player.canBuildCity()) {
						cout << "build city" << "\n";
						handleBuildCity(player);
						player.removeResource(GRAIN, 2);
						player.removeResource(ORE, 3);
						NotLegalMove = false;
					}
					else if (moveInput == "5" && player.canBuildRoad()) {
						cout << "build road" << "\n";
						handleBuildRoad(player);
						player.removeResource(LUMBER, 1);
						player.removeResource(BRICK, 1);
						NotLegalMove = false;
					}
					else if (moveInput == "6" && player.canBuyDev()) {
						cout << "buy dev card" << "\n";
						deck.buyDevelopmentCard(player);
						NotLegalMove = false;
					}
					else if (moveInput == "8") {
						cout << "trade with bank" << "\n";
						tradeBank(player);
						NotLegalMove = false;
					}
					else if (moveInput == "9") {
						cout << "trade with players" << "\n";
						playerTrading(player);
						NotLegalMove = false;
					}
					else if (moveInput == "e") {
						cout << "ending turn" << "\n";
						NotLegalMove = false;
						endOfTurn = true;
					}
					else if (moveInput == "p") {
						NotLegalMove = false;
						printInfoPlayers();
						//cout << player.toString() <<"\n";
					}
					else {
						cout << "Illegal move. Choose a valid move from the options above" << "\n";
					}
				}

				if (player.getVictoryPoints() >= VICTORYNUM) {
					cout << player.getName() + " won!\n";
					return;
				}
			}


		}
	}
}

// returns a string with possible moves a player can take
std::string GameEngine::possibleMoves(Player& player, TurnStage stage) {
	std::string possible = "";
	switch (stage) {
	case START:
		possible += "1 - roll dice\n";
		if (player.canPlayDev()) {
			possible += "2 - play development card\n";
		}
		break;
	case ROLLED:
		if (player.canPlayDev()) {
			possible += "2 - play development card\n";
		}
		if (player.canBuildSettlement()) {
			possible += "3 - build settlement\n";
		}
		if (player.canBuildCity()) {
			possible += "4 - build city\n";
		}
		if (player.canBuildRoad()) {
			possible += "5 - build road\n";
		}
		if (player.canBuyDev()) {
			possible += "6 - buy development card\n";
		}

		possible += "8 - trade with bank\n";
		possible += "9 - trade with players\n";
		possible += "e - end turn\n";
		possible += "p - print info\n";
		break;
	default:
		break;
	}
	return possible;
}

// get info about all the players
void GameEngine::printInfoPlayers() {
	for (Player& player : players) {
		cout << player.toString() << "\n\n";
	}
}

// add initial resources depending on the second settlement
void GameEngine::addInitResources(Player& player) {
	std::array<int, 3> settlementLoc = player.getSettlements()[1].getLoc(); // coord of second settle
	cout << settlementLoc[0] << " " << settlementLoc[1] << " " << settlementLoc[2] << "\n";
	Tile* tile1Ptr = board.getTile(settlementLoc[0], settlementLoc[1]); // get the tile with these coord to see what resource to add
	player.addResource(tile1Ptr->produces(), 1); // add resources according to the type of tile

	// resources from two upper tiles
	if (settlementLoc[2] == TOP) {
		// upper right tile resource addition
		std::array<int, 2> neighbor1Coord{ tile1Ptr->getNeighborCoord(1) };
		Tile* neighbor1TilePtr = board.getTile(neighbor1Coord[0], neighbor1Coord[1]);
		player.addResource(neighbor1TilePtr->produces(), 1);

		// upper left tile resource addition
		std::array<int, 2> neighbor6Coord{ tile1Ptr->getNeighborCoord(6) };
		Tile* neighbor6TilePtr = board.getTile(neighbor6Coord[0], neighbor6Coord[1]);
		player.addResource(neighbor6TilePtr->produces(), 1);
	}

	// resources from two lower tiles
	if (settlementLoc[2] == BOTTOM) {
		// lower right tile resource addition
		std::array<int, 2> neighbor3Coord{ tile1Ptr->getNeighborCoord(3) };
		Tile* neighbor3TilePtr = board.getTile(neighbor3Coord[0], neighbor3Coord[1]);
		player.addResource(neighbor3TilePtr->produces(), 1);

		// lower left tile resource addition
		std::array<int, 2> neighbor4Coord{ tile1Ptr->getNeighborCoord(4) };
		Tile* neighbor4TilePtr = board.getTile(neighbor4Coord[0], neighbor4Coord[1]);
		player.addResource(neighbor4TilePtr->produces(), 1);
	}
}

// distribute resources depending on the rolled dice number
void GameEngine::distributeResources(unsigned int diceNum) {
	std::vector<int> receivedResources{ 0,0,0,0 };
	std::vector<Tile> tilesWithDiceNum{ board.findTilesWithDiceNum(diceNum) };
	for (Tile& tile : tilesWithDiceNum) {
		std::array<int, 2> tileCoord{ tile.getCoord() };
		Resource res{ tile.produces() };
		std::array<std::array<int, 3>, 6> corners{ board.getSixCorners(tileCoord[0], tileCoord[1]) };
		for (auto corner : corners) {
			for (int i{ 0 }; i < players.size(); i++ ) {
				if (players[i].hasSettlementAtCoord(corner[0], corner[1], corner[2])) {
					players[i].addResource(res, NUMRESSET);
					receivedResources[i] += NUMRESSET;
				}
				if (players[i].hasCityAtCoord(corner[0], corner[1], corner[2])) {
					players[i].addResource(res, NUMRESCITY);
					receivedResources[i] += NUMRESCITY;
				}
			}
		}
	}
	for (int i{ 0 }; i < players.size(); i++) {
		cout << players[i].getName() + ": + " + to_string(receivedResources[i]) + "\n";
	}
	printInfoPlayers();
}

// roll dice 
unsigned int GameEngine::rollDice() {
	srand(static_cast<unsigned int>(time(0)));
	unsigned int a;
	unsigned int b;
	unsigned int c;
	a = 1 + rand() % 6;
	b = 1 + rand() % 6;
	c = a + b;
	cout << a << " + " << b << " = " << c << "\n";
	return c;

}

// handle roll dice
void GameEngine::handleRollDice(Player& player) {
	unsigned int rolledNum = rollDice();
	if (rolledNum == 7) { 
		discardResources();
		handleRobber(player);
	}
	else {
		distributeResources(rolledNum);
	}
}

// handle settlement building
void GameEngine::handleBuildSettlement(Player& player) {
	bool illegalLoc{ true };
	while (illegalLoc) {
		cout << player.getName() + ", choose the location of your settlement (x, y, top/bot): \n";
		int x;
		int y;
		string z;
		TileIntersection intersec;
		cin >> x >> y >> z;
		while (std::cin.fail() || !(z=="bot" || z=="top")) {
			std::cout << "Incorrect location. Try again.\n" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> x >> y >> z;
		}
		if (z == "bot") {
			intersec = BOTTOM;
		}
		else {
			intersec = TOP;
		}
		if (putInSea(x, y, intersec)) {
			cout << "Hey! Don't put your settlement in the sea!\n";
		}
		else if (cornerFree(x, y, intersec)) {
			player.buildSettlement(x, y, intersec);
			illegalLoc = false;
		}
		else {
			cout << "incorrect location. Try again. \n";
		}
	}
	drawUpdate();
	std::cin.clear();
	std::cin.ignore(256, '\n');
}

// handle city building
void GameEngine::handleBuildCity(Player& player) {
	bool illegalLoc{ true };
	while (illegalLoc) {
		cout << "choose the location of your city: \n";
		int x;
		int y;
		string z;
		TileIntersection intersec;
		cin >> x >> y >> z;
		while (std::cin.fail() || !(z == "bot" || z == "top")) {
			std::cout << "Incorrect location. Try again.\n" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> x >> y >> z;
		}
		if (z == "bot") {
			intersec = BOTTOM;
		}
		else {
			intersec = TOP;
		}
		if (player.hasSettlementAtCoord(x, y, intersec)) {
			player.buildCity(x, y, intersec);
			cout << "settlement was upgraded to city\n";
			illegalLoc = false;
		}
		else {
			cout << "you don't have a settlement on this location. Try again. \n";
		}
	}
	drawUpdate();
	std::cin.clear();
	std::cin.ignore(256, '\n');
}

// handle road building
void GameEngine::handleBuildRoad(Player& player) {
	bool illegalLoc{ true }; // road is already build on this coord
	bool illegalCorner{ true }; // no property on the corresponding corner to build a road
	while (illegalLoc || illegalCorner) {
		cout << player.getName() + ", choose the location of your road (x, y, up/right/down): \n";
		int x;
		int y;
		string z;
		TileEdge edge;
		cin >> x >> y >> z;
		while (std::cin.fail() || !(z == "up" || z == "right" || z == "down")) {
			std::cout << "Incorrect location. Try again.\n" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> x >> y >> z;
		}
		if (z == "up") {
			edge = UP;
		}
		else if (z == "right") {
			edge = RIGHT;
		}
		else {
			edge = DOWN;
		}

		// get corners at road tile to be able to check if there is a property on one of corners 
		std::array<std::array<int, 3>, 6> sixCorners{ board.getSixCorners(x, y) };

		// corners to check depend on the edge
		switch (edge) {
		case UP:
			if ((player.hasPropertyAtCoord(sixCorners[0][0], sixCorners[0][1], sixCorners[0][2])) 
			 || (player.hasPropertyAtCoord(sixCorners[1][0], sixCorners[1][1], sixCorners[1][2]))
			 || (player.canContRoad(x, y, edge))) {
				illegalCorner = false;
				if (roadAvailable(x, y, edge)) {
					player.buildRoad(x, y, edge);
					illegalLoc = false;
				}
			}
			break;
		case RIGHT:
			if ((player.hasPropertyAtCoord(sixCorners[1][0], sixCorners[1][1], sixCorners[1][2]))
			 || (player.hasPropertyAtCoord(sixCorners[2][0], sixCorners[2][1], sixCorners[2][2]))
			 || (player.canContRoad(x, y, edge))) {
				illegalCorner = false;
				if (roadAvailable(x, y, edge)) {
					player.buildRoad(x, y, edge);
					illegalLoc = false;
				}
			}
			break;
		case DOWN:
			if ((player.hasPropertyAtCoord(sixCorners[2][0], sixCorners[2][1], sixCorners[2][2]))
			 || (player.hasPropertyAtCoord(sixCorners[3][0], sixCorners[3][1], sixCorners[3][2]))
			 || (player.canContRoad(x, y, edge))) {
				illegalCorner = false;
				if (roadAvailable(x, y, edge)) {
					player.buildRoad(x, y, edge);
					illegalLoc = false;
				}
			}
			break;
		default:
			cout << "smth wrong\n";
		}

		if (illegalCorner) { cout << "you don't have a city/settlement/road here. Choose other coordinates\n"; }
		else if (illegalLoc) { cout << "this road is occupied. Choose other coordinates\n"; }
	}
	drawUpdate();
	std::cin.clear();
	std::cin.ignore(256, '\n');
}

// handle robber function that is called when dice roll result is 7 or Knight card is played
// move the robber, then randomly draw a resource card from the player on the new tile and add it to the player in turn
void GameEngine::handleRobber(Player& player) {
	// set location of the robber
	std::array <int, 2> newLoc;
	int playerindex;
	bool incorrectInput{ true };
	while (incorrectInput) {
		cout << player.getName() + ", enter new tile coordinates for the robber (x, y):\n";
		cin >> newLoc[0] >> newLoc[1];
		while (std::cin.fail()) {
			std::cout << "Incorrect location. Try again.\n" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> newLoc[0] >> newLoc[1];
		}

		// check that new location is different than the old one
		std::array <int, 2> oldLoc;
		oldLoc = robber.getLoc();
		if (newLoc[0] == oldLoc[0] && newLoc[1] == oldLoc[1]) {
			cout << "same location is not allowed. Try again.\n";
		}
		else {
			incorrectInput = false;
		}

		// check that new location is not in the sea
		if (board.hasTile(newLoc[0], newLoc[1])) {
			if (board.getTile(newLoc[0], newLoc[1])->getTerrainType() == SEA) {
				cout << "Hey! Don't put the robber in the sea!\n";
				incorrectInput = true;
			}
		}
		else {
			incorrectInput = true;
			cout << "Hey! Don't put the robber in the sea!\n";
		}
	}
	std::cin.clear();
	std::cin.ignore(256, '\n');

	// set the location using new coordinates
	robber.setLoc(newLoc[0], newLoc[1]);
	drawUpdate();

	//act based on the vector size
	//vector <int> playercount;
	int playercount = 0;
	cout << "which player do you want to rob:\n";
	for (int i = 0; i < players.size(); ++i) {
		if (players[i].getColor() == player.getColor()) {
			//break;
		}
		else if (playersOnTile(players[i], newLoc[0], newLoc[1])) {
			playersOnTile(players[i], newLoc[0], newLoc[1]);
			cout << i << " " << players[i].getName() << endl;
			playercount += 1;
		}
	}


	if (playercount == 0) {
		cout << "no players on the tile chosen. nothing to do\n" << endl;
		return;
	}
	else {
		cin >> playerindex;
		//random index draw
		srand(time(NULL));
		int index = rand() % players[playerindex].getNumResources();
		if (index < players[playerindex].getNumGrain()) {
			players[playerindex].removeResource(GRAIN, 1);
			player.addResource(GRAIN, 1);
		}
		else if (index < players[playerindex].getNumGrain() + players[playerindex].getNumBrick()) {
			players[playerindex].removeResource(BRICK, 1);
			player.addResource(BRICK, 1);
		}
		else if (index < players[playerindex].getNumGrain() + players[playerindex].getNumBrick() + players[playerindex].getNumWool()) {
			players[playerindex].removeResource(WOOL, 1);
			player.addResource(WOOL, 1);
		}
		else if (index < players[playerindex].getNumGrain() + players[playerindex].getNumBrick() + players[playerindex].getNumWool() + players[playerindex].getNumLumber()) {
			players[playerindex].removeResource(LUMBER, 1);
			player.addResource(LUMBER, 1);
		}
		else if (index < players[playerindex].getNumGrain() + players[playerindex].getNumBrick() + players[playerindex].getNumWool() + players[playerindex].getNumLumber() + players[playerindex].getNumOre()) {
			players[playerindex].removeResource(ORE, 1);
			player.addResource(ORE, 1);
		}
		else;
	}
}

// find players on tile
bool GameEngine::playersOnTile(Player& p, int x, int y) {
	array<array<int, 3>, 6> sixCorners;
	sixCorners = board.getSixCorners(x, y);
	for (auto c : sixCorners) {
		if (p.hasPropertyAtCoord(c[0], c[1], c[2])) {
			return true;
		}
	}
	return false;
}


// play development card
void GameEngine::playDevCard(Player& player) {
	int choise{ 0 };
	vector<DevelopmentCard> cards = player.returnDevcards();
	cout << "Which development card would you like to play:\n";
	for (int index = 0; index < cards.size(); ++index) {
		if (cards[index].getType() == VICTORY) {
			cout << "   VICTORY" << endl;
		}
		else {
			string type = cards[index].toString();
			cout << index + 1 << "  " << type << endl;
		}
	}
	cin >> choise;
	Devtype chosentype = cards[choise - 1].getType();
	string z;
	string type;
	string grain = "GRAIN";
	string brick = "BRICK";
	switch (chosentype) {
	case KNIGHT:
		handleRobber(player);
		cout << "played a knight card\n";
		break;
	case ROADBUILDING:
		int x, y;
		TileEdge edge;
		cout << "identify location for first road:\n";
		cin >> x >> y >> z;
		if (z == "UP") {
			edge = UP;
		}
		else if (z == "RIGHT") {
			edge = RIGHT;
		}
		else {
			edge = DOWN;
		}
		player.buildRoad(x, y, edge);
		drawUpdate();
		cout << "identify location for second road:\n";
		cin >> x >> y >> z;
		if (z == "UP") {
			edge = UP;
		}
		else if (z == "RIGHT") {
			edge = RIGHT;
		}
		else {
			edge = DOWN;
		}
		player.buildRoad(x, y, edge);
		drawUpdate();
		break;
	case YEAROFPLENTY:
		for (int i = 0; i < 2; ++i) {
		label:
			cout << "identify the resource that you want to add:\n";
			cin >> type;
			cout << type;
			if (type == "GRAIN") { 
				player.addResource(GRAIN, 1);
			}
			else if (type == "BRICK") {
				player.addResource(BRICK, 1);
			}
			else if (type == string("WOOL")) {
				player.addResource(WOOL, 1);
			}
			else if (type == string("LUMBER")) {
				player.addResource(LUMBER, 1);
			}
			else if (type == string("ORE")) {
				player.addResource(ORE, 1);
			}
			else {
				goto label;
			}
		}
		break;
	case MONOPOLY:
		cout << "what type of reasource would you like to take\n";
		cin >> z;
		if (z == "GRAIN") {
			for (auto e : players) {
				if (e.getName() == player.getName()) {
				}
				else {
					player.addResource(GRAIN, e.getNumGrain());
					e.removeResource(GRAIN, e.getNumGrain());
				}
			}
		}
		else if (z == "BRICK") {
			for (auto e : players) {
				if (e.getName() == player.getName()) {
				}
				else {
					player.addResource(BRICK, e.getNumGrain());
					e.removeResource(BRICK, e.getNumGrain());
				}
			}
		}
		else if (z == "WOOL") {
			for (auto e : players) {
				if (e.getName() == player.getName()) {
				}
				else {
					player.addResource(WOOL, e.getNumGrain());
					e.removeResource(WOOL, e.getNumGrain());
				}
			}
		}
		else if (z == "LUMBER") {
			for (auto e : players) {
				if (e.getName() == player.getName()) {
				}
				else {
					player.addResource(GRAIN, e.getNumGrain());
					e.removeResource(GRAIN, e.getNumGrain());
				}
			}
		}
		else if (z == "ORE") {
			for (auto e : players) {
				if (e.getName() == player.getName()) {
				}
				else {
					player.addResource(GRAIN, e.getNumGrain());
					e.removeResource(GRAIN, e.getNumGrain());
				}
			}
		}
	default:
		break;
	}
	player.removeDevCard(chosentype);
	cout << player.toString();
}

// update special cards (longest road, largest army) owners if necesssary
void GameEngine::updateSpecialCards() {
	for (auto p : players) {
		if (p.hasLargestArmy()) {
			Player currentowner = p;
			for (auto p : players) {
				if (p.getNumKnightcards() > currentowner.getNumKnightcards()) {
					p.addspecialCard(LARGESTARMY);
					currentowner.removespecialCard(LARGESTARMY);
					cout << "new owner of specialcard" << p.getName() << endl;
				}
			}
			break;
		}
	}
	for (auto p : players) {
		if (p.getNumKnightcards() >= 3) {
			p.addspecialCard(LARGESTARMY);
			cout << "new owner of specialcard" << p.getName() << endl;
		}
	}
}

// player trading with bank
void GameEngine::tradeBank(Player& player) {
start:
	int amount;
	string type;
	string type2;
	Resource giventype{ NORES };
	Resource wantedtype{ NORES };
	//cout << "specify the resource types to be traded with the bank followed by the type you want to receive\n";
	//cout << "followed by the amount you would like to receive (trading rate 4:1):" << endl;
	cout << "specify your deal: give get amount\n";
	cout << "example: {grain, brick, wool, lumber, ore} {grain, brick, wool, lumber, ore} n";
	cin >> type >> type2 >> amount;
	if (type == type2) {
		cout << "the two resource types specified are equal\n";
		goto start;
	}
	if (type == "grain") {
		if (player.getNumGrain() < amount * 4) {
			cout << "you do not have enough of this resource" << endl;
			return;
		}
		giventype = GRAIN;
	}
	else if (type == "brick") {
		if (player.getNumBrick() < amount * 4) {
			cout << "you do not have enough of this resource" << endl;
			return;
		}
		giventype = BRICK;
	}
	else if (type == "wool") {
		if (player.getNumWool() < amount * 4) {
			cout << "you do not have enough of this resource" << endl;
			return;
		}
		giventype = WOOL;
	}
	else if (type == "lumber") {
		if (player.getNumLumber() < amount * 4) {
			cout << "you do not have enough of this resource" << endl;
			return;
		}
		giventype = LUMBER;
	}
	else if (type == "ore") {
		if (player.getNumOre() < amount * 4) {
			cout << "you do not have enough of this resource" << endl;
			return;
		}
		giventype = ORE;
	}
	else {
		cout << "incorrect resource specified" << endl;
		goto start;
	}
	if (type2 == "grain") {
		wantedtype = GRAIN;
	}
	else if (type2 == "brick") {
		wantedtype = BRICK;
	}
	else if (type2 == "wool") {
		wantedtype = WOOL;
	}
	else if (type2 == "lumber") {
		wantedtype = LUMBER;
	}
	else if (type2 == "ore") {
		wantedtype = ORE;
	}
	player.addResource(wantedtype, amount);
	player.removeResource(giventype, amount * 4);
	cout << "trade succesful\n";
	cout << player.toString();
	return;
}

// trading between players
void GameEngine::playerTrading(Player& player) {
start:
	int playercount{ 0 };
	int playerindex;
	int currentplayerindex;
	int amount{ 0 };
	int amount2{ 0 };
	string type;
	string type2;
	Resource giventype{ NORES };
	Resource wantedtype{ NORES };
	string answer;
	cout << "specify the type you give followed by the amount:\n";
	cin >> type >> amount;
	while (std::cin.fail()) {
		std::cout << "Incorrect input. Try again.\n" << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> type >> amount;
	}
	cout << "specify the type you want to receive followed by the amount\n";
	cin >> type2 >> amount2;
	while (std::cin.fail()) {
		std::cout << "Incorrect input. Try again.\n" << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> type2 >> amount2;
	}

	if (type == type2) {
		cout << "the two resource types specified are equal\n";
		goto start;
	}
	if (type == "grain") {
		if (player.getNumGrain() < amount) {
			cout << "you do not have enough of this resource" << endl;
			return;
		}
		giventype = GRAIN;
	}
	else if (type == "brick") {
		if (player.getNumBrick() < amount) {
			cout << "you do not have enough of this resource" << endl;
			return;
		}
		giventype = BRICK;
	}
	else if (type == "wool") {
		if (player.getNumWool() < amount) {
			cout << "you do not have enough of this resource" << endl;
			return;
		}
		giventype = WOOL;
	}
	else if (type == "lumber") {
		if (player.getNumLumber() < amount) {
			cout << "you do not have enough of this resource" << endl;
			return;
		}
		giventype = LUMBER;
	}
	else if (type == "ore") {
		if (player.getNumOre() < amount) {
			cout << "you do not have enough of this resource" << endl;
			return;
		}
		giventype = ORE;
	}
	else {
		cout << "incorrect resource specified" << endl;
		goto start;
	}
	if (type2 == "grain") {
		wantedtype = GRAIN;
	}
	else if (type2 == "brick") {
		wantedtype = BRICK;
	}
	else if (type2 == "wool") {
		wantedtype = WOOL;
	}
	else if (type2 == "lumber") {
		wantedtype = LUMBER;
	}
	else if (type2 == "ore") {
		wantedtype = ORE;
	}
	else {
		cout << "incorrect resource specified" << endl;
		goto start;
	}

	cout << "who would you like to trade with:\n";
	for (int i = 0; i < players.size(); ++i) {
		if (players[i].getColor() != player.getColor() && players[i].hasResource(wantedtype, amount2)) {
			cout << i << " " << players[i].getName() << endl;
			playercount += 1;
		}
		if (players[i].getColor() == player.getColor()) {
			currentplayerindex = i;
		}
	}
	cin >> playerindex;
	while (std::cin.fail() || !(playerindex>=0 || playerindex<players.size())) {
		std::cout << "Incorrect input. Try again.\n" << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> playerindex;
	}

question:
	cout << players[playerindex].getName() << endl << "the following player would like to make the following trade with you:" << player.getName() << endl;
	cout << "you receive: " << amount << " " << type << endl;
	cout << "in exchange for: " << amount2 << " " << type2 << endl;
	cout << "would you like to accept this trade? (yes/no)\n";
	cin >> answer;
	cout << endl << "before:\n";
	cout << players[currentplayerindex].toString() << endl;
	cout << players[playerindex].toString() << endl;
	if (answer == "no") {
		cout << player.getName();
		cout << "the other player did no accept the trade\n";
		return;
	}
	else if (answer == "yes") {
		players[playerindex].removeResource(wantedtype, amount2);
		players[currentplayerindex].addResource(wantedtype, amount2);
		players[playerindex].addResource(giventype, amount);
		players[currentplayerindex].removeResource(giventype, amount);

	}
	else {
		cout << "incorrect answer\n";
		goto question;
	}
	cout << "trade was succesfull:\n";
	cout << players[currentplayerindex].toString() << endl;
	cout << players[playerindex].toString() << endl;

	std::cin.clear();
	std::cin.ignore(256, '\n');
}

// check whether a player wants to place a settlement into the sea
bool GameEngine::putInSea(int x, int y, TileIntersection z) {
	std::array<std::array<int, 3>, 3> adjCorners{ board.getAdjacentCorners(x, y, z) };
	int numExistingTiles{ 0 }; // number of tiles that exist among the adjacent corners
	for (int i{ 0 }; i < 3; i++) {
		if (board.hasTile(adjCorners[i][0], adjCorners[i][1])) {
			numExistingTiles++;
		}
	}
	if (numExistingTiles >= 2) {
		return false;
	}
	return true;
}

// discard resources (when 7 i rolled)
void GameEngine::discardResources() {
	for (int i{ 0 }; i < players.size(); i++) {
		size_t numRes{ players[i].getNumResources() };
		size_t numDiscard{numRes/2};
		if (numRes >= 8) {
			cout << "\n" + players[i].getName() + ", you must discard " + to_string(numDiscard) + " resources\n";
			cout << "you have the following resources:\n";
			cout << "grain: " + std::to_string(players[i].getNumGrain()) + "\n"
				"brick: " + std::to_string(players[i].getNumBrick()) + "\n"
				"wool: " + std::to_string(players[i].getNumWool()) + "\n"
				"lumber: " + std::to_string(players[i].getNumLumber()) + "\n"
				"ore: " + std::to_string(players[i].getNumOre()) + "\n";
			cout << "specify in vector form the resources to discard\n";
			cout <<	"example: 1 0 2 1 0\n";
			int r1;
			int r2;
			int r3;
			int r4;
			int r5;
			cin >> r1 >> r2 >> r3 >> r4 >> r5;
			// check input inside while
			while (std::cin.fail() || !((r1+r2+r3+r4+r5)==numDiscard) || 
			r1 < 0 ||
			r2 < 0 ||
			r3 < 0 ||
			r4 < 0 ||
			r5 < 0 ||
			r1>players[i].getNumGrain() ||
			r2>players[i].getNumBrick() ||
			r3>players[i].getNumWool() ||
			r4>players[i].getNumLumber() ||
			r5>players[i].getNumOre()) {
				std::cout << "Incorrect vector. Try again.\n" << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cin >> r1 >> r2 >> r3 >> r4 >> r5;
			}

			players[i].removeResource(GRAIN, r1);
			players[i].removeResource(BRICK, r2);
			players[i].removeResource(WOOL, r3);
			players[i].removeResource(LUMBER, r4);
			players[i].removeResource(ORE, r5);

		}
	}
	std::cin.clear();
	std::cin.ignore(256, '\n');
}

// test function SDL2
void GameEngine::testSDLGE() {
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
				std::vector<Tile> tilesToDraw{ board.getTiles() };
				for (Tile& tile : tilesToDraw) {
					drawTile(renderer, tile);
				}

				// settlements
				for (Player& player : players) {
					for (const Settlement& settlement : player.getSettlements()) {
						drawSettlement(renderer, settlement, player.getColor());
					}
				}

				// roads
				for (Player& player : players) {
					for (const Road& road : player.getRoads()) {
						drawRoad(renderer, road, player.getColor());
					}
				}

				// robber
				drawRobber(renderer, robber);


				SDL_RenderPresent(renderer);
				done = SDL_TRUE;
			}
		}
	}
}

// draw tile
void GameEngine::drawTile(SDL_Renderer* renderer, Tile& tile) {
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

	SDL_SetRenderDrawColor(renderer, R, G, B, 130);//SDL_ALPHA_OPAQUE

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

	// draw number
	drawNum(renderer, x, y, tile.getDiceNum());
}

// draw road
void GameEngine::drawRoad(SDL_Renderer* renderer, const Road& road, std::string color) {
	int WIDTH{ 800 };
	int HEIGHT{ 600 };
	std::array<int, 2> CENTER{ WIDTH / 2, HEIGHT / 2 };
	int RADIUS{ 40 };
	int RADCOS{ static_cast<int>(round(RADIUS*sqrt(3) / 2)) };

	std::array<int, 3> roadCoord{ road.getLoc() };
	int x{ CENTER[0] + 2 * roadCoord[0] * (RADCOS + 1) - roadCoord[1] * (RADCOS + 1) };
	int y{ CENTER[1] - roadCoord[1] * (RADIUS + RADIUS / 2 + 2) };

	if (color == "red"){ SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); }
	else if (color == "green") { SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE); }
	else if (color == "blue") { SDL_SetRenderDrawColor(renderer, 0, 255, 255, SDL_ALPHA_OPAQUE); }
	else if (color == "yellow") { SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE); }
	else { SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); }

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

// draw settlement
void GameEngine::drawSettlement(SDL_Renderer* renderer, const Settlement& settlement, std::string color) {
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

	if (color == "red") { SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); }
	else if (color == "green") { SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE); }
	else if (color == "blue") { SDL_SetRenderDrawColor(renderer, 0, 255, 255, SDL_ALPHA_OPAQUE); }
	else if (color == "yellow") { SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE); }
	else { SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); }

	switch (settlementCoord[2]) {
	case TOP:
		srcrect.x = x - 7;
		srcrect.y = y - RADIUS - 7;
		srcrect.w = 14;
		srcrect.h = 14;
		//SDL_RenderDrawRect(renderer, rectPtr);
		drawCircle(renderer, x, y - RADIUS, 7);
		break;
	case BOTTOM:
		srcrect.x = x - 7;
		srcrect.y = y + RADIUS - 7;
		srcrect.w = 14;
		srcrect.h = 14;
		//SDL_RenderDrawRect(renderer, rectPtr);
		drawCircle(renderer, x, y + RADIUS, 7);
		break;
	default:
		std::cout << "smth wrong\n";
		break;
	}
}

// draw city
void GameEngine::drawCity(SDL_Renderer* renderer, const City& city, std::string color) {
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

	if (color == "red") { SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); }
	else if (color == "green") { SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE); }
	else if (color == "blue") { SDL_SetRenderDrawColor(renderer, 0, 255, 255, SDL_ALPHA_OPAQUE); }
	else if (color == "yellow") { SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE); }
	else { SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); }

	switch (cityCoord[2]) {
	case TOP:
		srcrect.x = x - 7;
		srcrect.y = y - RADIUS - 7;
		srcrect.w = 14;
		srcrect.h = 14;
		//SDL_RenderDrawRect(renderer, rectPtr);
		//SDL_RenderFillRect(renderer, rectPtr);
		drawFilledCircle(renderer, x, y - RADIUS, 7);
		break;
	case BOTTOM:
		srcrect.x = x - 7;
		srcrect.y = y + RADIUS - 7;
		srcrect.w = 14;
		srcrect.h = 14;
		//SDL_RenderDrawRect(renderer, rectPtr);
		//SDL_RenderFillRect(renderer, rectPtr);
		drawFilledCircle(renderer, x, y + RADIUS, 7);
		break;
	default:
		std::cout << "smth wrong\n";
		break;
	}
}

// draw robber
void GameEngine::drawRobber(SDL_Renderer* renderer, Robber& robber) {
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

// main drawing function. Draws everything on the screen by calling draw-functions
void GameEngine::drawUpdate() {
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	//SDL_RenderClear(renderer);

	// close the current window and make a new one
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);
	SDL_SetWindowPosition(window, 500, 75);

	// draw tiles
	std::vector<Tile> tilesToDraw{ board.getTiles() };
	for (Tile& tile : tilesToDraw) {
		drawTile(renderer, tile);
	}

	// draw settlements
	for (Player& player : players) {
		for (const Settlement& settlement : player.getSettlements()) {
			drawSettlement(renderer, settlement, player.getColor());
		}
	}

	// draw cities
	for (Player& player : players) {
		for (const City& city : player.getCities()) {
			drawCity(renderer, city, player.getColor());
		}
	}

	// draw roads
	for (Player& player : players) {
		const std::vector<Road> playerRoads{ player.getRoads() };
		for (const Road& road : playerRoads) {
			drawRoad(renderer, road, player.getColor());
		}
	}

	// draw robber
	drawRobber(renderer, robber);

	// draw circle
	drawCircle(renderer, 50, 50, 10);


	SDL_RenderPresent(renderer);
}

// draw dice number on the tile
void GameEngine::drawNum(SDL_Renderer* renderer, int x, int y, int num) {
	int NUM_WIDTH{3};
	int NUM_HEIGHT{ 6 };

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	// middle
	if (num == 2 || num == 3 || num == 4 || num == 5 || num == 6 || num == 8 || num == 9) {
		SDL_RenderDrawLine(renderer, x - NUM_WIDTH, y, x + NUM_WIDTH, y);
	}

	// top
	if (num == 2 || num == 3 || num == 5 || num == 6 || num == 7 || num == 8 || num == 9) {
		SDL_RenderDrawLine(renderer, x - NUM_WIDTH, y - NUM_HEIGHT, x + NUM_WIDTH, y - NUM_HEIGHT);
	}

	// bottom
	if (num == 2 || num == 3 || num == 5 || num == 6 || num == 8 || num == 9) {
		SDL_RenderDrawLine(renderer, x - NUM_WIDTH, y + NUM_HEIGHT, x + NUM_WIDTH, y + NUM_HEIGHT);
	}

	// up right
	if (num == 2 || num == 3 || num == 4 || num == 7 || num == 8 || num == 9) {
		SDL_RenderDrawLine(renderer, x + NUM_WIDTH, y - NUM_HEIGHT, x + NUM_WIDTH, y);
	}

	// down right
	if (num == 3 || num == 4 || num == 5 || num == 6 || num == 7 || num == 8 || num == 9) {
		SDL_RenderDrawLine(renderer, x + NUM_WIDTH, y, x + NUM_WIDTH, y + NUM_HEIGHT);
	}

	// up left
	if (num == 4 || num == 5 || num == 6 || num == 8 || num == 9) {
		SDL_RenderDrawLine(renderer, x - NUM_WIDTH, y - NUM_HEIGHT, x - NUM_WIDTH, y);
	}

	// down left
	if (num == 2 || num == 6 || num == 8) {
		SDL_RenderDrawLine(renderer, x - NUM_WIDTH, y, x - NUM_WIDTH, y + NUM_HEIGHT);
	}

	// 10 11 12
	if (num == 10 || num == 11 || num == 12) {
		SDL_RenderDrawLine(renderer, x - NUM_WIDTH, y - NUM_HEIGHT, x - NUM_WIDTH, y);
		SDL_RenderDrawLine(renderer, x - NUM_WIDTH, y, x - NUM_WIDTH, y + NUM_HEIGHT);
	}

	// 10
	if (num == 10) {
		x += NUM_WIDTH;
		SDL_RenderDrawLine(renderer, x - NUM_WIDTH, y - NUM_HEIGHT, x + NUM_WIDTH, y - NUM_HEIGHT);
		SDL_RenderDrawLine(renderer, x - NUM_WIDTH, y + NUM_HEIGHT, x + NUM_WIDTH, y + NUM_HEIGHT);
		SDL_RenderDrawLine(renderer, x + NUM_WIDTH, y - NUM_HEIGHT, x + NUM_WIDTH, y);
		SDL_RenderDrawLine(renderer, x + NUM_WIDTH, y, x + NUM_WIDTH, y + NUM_HEIGHT);
		SDL_RenderDrawLine(renderer, x - NUM_WIDTH, y - NUM_HEIGHT, x - NUM_WIDTH, y);
		SDL_RenderDrawLine(renderer, x - NUM_WIDTH, y, x - NUM_WIDTH, y + NUM_HEIGHT);
	}

	// 11
	if (num == 11) {
		x += 2*NUM_WIDTH;
		SDL_RenderDrawLine(renderer, x - NUM_WIDTH, y - NUM_HEIGHT, x - NUM_WIDTH, y);
		SDL_RenderDrawLine(renderer, x - NUM_WIDTH, y, x - NUM_WIDTH, y + NUM_HEIGHT);
	}

	// 12
	if (num == 12) {
		x += NUM_WIDTH;
		SDL_RenderDrawLine(renderer, x - NUM_WIDTH, y - NUM_HEIGHT, x + NUM_WIDTH, y - NUM_HEIGHT);
		SDL_RenderDrawLine(renderer, x + NUM_WIDTH, y - NUM_HEIGHT, x + NUM_WIDTH, y);
		SDL_RenderDrawLine(renderer, x - NUM_WIDTH, y, x + NUM_WIDTH, y);
		SDL_RenderDrawLine(renderer, x - NUM_WIDTH, y, x - NUM_WIDTH, y + NUM_HEIGHT);
		SDL_RenderDrawLine(renderer, x - NUM_WIDTH, y + NUM_HEIGHT, x + NUM_WIDTH, y + NUM_HEIGHT);
	}
}

// draw circle(settlement)
void GameEngine::drawCircle(SDL_Renderer* renderer, int x, int y, int r) {
	for (int alpha{ 0 }; alpha < 360; alpha++) {
		double angle{ alpha * 3.14 / 180 };
		int rcosx{ static_cast<int>(floor(r * cos(angle))) };
		int rsiny{ static_cast<int>(floor(r * sin(angle))) };
		SDL_RenderDrawPoint(renderer, x + rcosx, y - rsiny);

		rcosx = static_cast<int>(round(r * cos(angle)));
		rsiny = static_cast<int>(round(r * sin(angle)));
		SDL_RenderDrawPoint(renderer, x + rcosx, y - rsiny);

		rcosx = static_cast<int>(ceil(r * cos(angle)));
		rsiny = static_cast<int>(ceil(r * sin(angle)));
		SDL_RenderDrawPoint(renderer, x + rcosx, y - rsiny);
	}
}

// draw filled circle (city)
void GameEngine::drawFilledCircle(SDL_Renderer* renderer, int x, int y, int r) {
	for (int alpha{ 0 }; alpha < 360; alpha++) {
		double angle{ alpha * 3.14 / 180 };
		int rcosx{ static_cast<int>(floor(r * cos(angle))) };
		int rsiny{ static_cast<int>(floor(r * sin(angle))) };
		SDL_RenderDrawPoint(renderer, x + rcosx, y - rsiny);
		SDL_RenderDrawLine(renderer, x, y, x + rcosx, y - rsiny);

		rcosx = static_cast<int>(round(r * cos(angle)));
		rsiny = static_cast<int>(round(r * sin(angle)));
		SDL_RenderDrawPoint(renderer, x + rcosx, y - rsiny);
		SDL_RenderDrawLine(renderer, x, y, x + rcosx, y - rsiny);

		rcosx = static_cast<int>(ceil(r * cos(angle)));
		rsiny = static_cast<int>(ceil(r * sin(angle)));
		SDL_RenderDrawPoint(renderer, x + rcosx, y - rsiny);
		SDL_RenderDrawLine(renderer, x, y, x + rcosx, y - rsiny);

	}
}