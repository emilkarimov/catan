/// \file
/// GameEngine.cpp
/// GameEngine class member-function definitions.

#include "GameEngine.h" // Robber class definition
#include <iostream>
#include <string>
using namespace std;

// number of resources distributed for settlements and cities
unsigned int NUMRESSET{ 1 };
unsigned int NUMRESCITY{ 2 };

// constructor 
GameEngine::GameEngine(std::vector<Player> players, Board board)
	: players(players), board(board) {

}

// start game
void GameEngine::start() {

}

// checks if a corner is available for placing a settlement
bool GameEngine::cornerFree(int x, int y, TileIntersection intersec) {
	std::array<std::array<int, 3>, 3> corners;
	corners = board.getAdjacentCorners(x, y, intersec);
	for (unsigned int i{ 0 }; i < 3; ++i) {
		for (Player& player : players) {
			if (player.hasPropertyAtCoord(corners[i][0], corners[i][1], corners[i][2])) {
				return false;
			}
		}
	}
	return true;
}

// 1st stage - players build two settlements and two roads
void GameEngine::firstStage() {
	// first settlement and road
	for (unsigned int i{ 0 }; i < players.size(); ++i) {
		// settlement
		cout << players[i].getName() + ", choose the location of your first settlement: \n";
		int x;
		int y;
		string z;
		TileIntersection intersec;
		cin >> x >> y >> z;
		if (z == "BOTTOM") {
			intersec = BOTTOM;
		}
		else {
			intersec = TOP;
		}
		cout << "corner free?: " << cornerFree(x, y, intersec) << "\n"; // check location
		players[i].buildSettlement(x, y, intersec);

		// road
		cout << players[i].getName() + ", now select the location of your first road: \n";
		cin >> x >> y >> z;
		TileEdge edge;
		if (z == "UP") {
			edge = UP;
		}
		else if (z == "RIGHT") {
			edge = RIGHT;
		}
		else {
			edge = DOWN;
		}
		players[i].buildRoad(x, y, edge);
	}

	// second settlement and road
	for (int i{ static_cast<int>(players.size()) - 1 }; i > -1; --i) {
		// settlement
		cout << players[i].getName() + ", choose the location of your second settlement: \n";
		int x;
		int y;
		string z;
		TileIntersection intersec;
		cin >> x >> y >> z;
		if (z == "BOTTOM") {
			intersec = BOTTOM;
		}
		else {
			intersec = TOP;
		}
		cout << "corner free?: " << cornerFree(x, y, intersec) << "\n"; // check location
		players[i].buildSettlement(x, y, intersec);
		addInitResources(players[i]); // add initial resources 

									  // road
		cout << players[i].getName() + ", now select the location of your second road: \n";
		cin >> x >> y >> z;
		TileEdge edge;
		if (z == "UP") {
			edge = UP;
		}
		else if (z == "RIGHT") {
			edge = RIGHT;
		}
		else {
			edge = DOWN;
		}
		players[i].buildRoad(x, y, edge);
	}
}


// 2nd stage - players take actions in turn
void GameEngine::secondStage() {
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
				NotLegalMove = false;
			}
			else if (moveInput == "2" && player.canPlayDev()) {
				cout << "Play development card" << "\n";
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
			endOfTurn = true;
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
	//players[0].toString();
}

// add initial resources depending on the second settlement
void GameEngine::addInitResources(Player& player) {
	std::array<int, 3> settlementLoc = player.getSettlements()[1].getLoc(); // coord of second settle
	cout << settlementLoc[0] << " " << settlementLoc[1] << " " << settlementLoc[2] << "\n";
	Tile* tile1Ptr = board.getTile(settlementLoc[0], settlementLoc[1]); // get the tile with these coord to see what resource to add
	cout << tile1Ptr->toString() << "\n";
	player.addResource(tile1Ptr->produces(), 1); // add resources according to the type of tile

	// resources from two upper tiles
	if (settlementLoc[2] == TOP) {
		// upper right tile resource addition
		std::array<int, 2> neighbor1Coord{ tile1Ptr->getNeighborCoord(1) };
		cout << "neighbor1 coord: " << neighbor1Coord[0] << " " << neighbor1Coord[1] << "\n";
		Tile* neighbor1TilePtr = board.getTile(neighbor1Coord[0], neighbor1Coord[1]);
		player.addResource(neighbor1TilePtr->produces(), 1);

		// upper left tile resource addition
		std::array<int, 2> neighbor6Coord{ tile1Ptr->getNeighborCoord(6) };
		cout << "neighbor6 coord: " << neighbor6Coord[0] << " " << neighbor6Coord[1] << "\n";
		Tile* neighbor6TilePtr = board.getTile(neighbor6Coord[0], neighbor6Coord[1]);
		player.addResource(neighbor6TilePtr->produces(), 1);
	}

	// resources from two lower tiles
	if (settlementLoc[2] == BOTTOM) {
		// lower right tile resource addition
		std::array<int, 2> neighbor3Coord{ tile1Ptr->getNeighborCoord(3) };
		cout << "neighbor3 coord: " << neighbor3Coord[0] << " " << neighbor3Coord[1] << "\n";
		Tile* neighbor3TilePtr = board.getTile(neighbor3Coord[0], neighbor3Coord[1]);
		player.addResource(neighbor3TilePtr->produces(), 1);

		// lower left tile resource addition
		std::array<int, 2> neighbor4Coord{ tile1Ptr->getNeighborCoord(4) };
		cout << "neighbor4 coord: " << neighbor4Coord[0] << " " << neighbor4Coord[1] << "\n";
		Tile* neighbor4TilePtr = board.getTile(neighbor4Coord[0], neighbor4Coord[1]);
		player.addResource(neighbor4TilePtr->produces(), 1);
	}
}


// distribute resources depending on the rolled dice number
void GameEngine::distributeResources(unsigned int diceNum) {
	std::vector<Tile> tilesWithDiceNum{ board.findTilesWithDiceNum(diceNum) };
	for (Tile& tile : tilesWithDiceNum) {
		std::array<int, 2> tileCoord{ tile.getCoord() };
		Resource res{ tile.produces() };
		std::array<std::array<int, 3>, 6> corners{ board.getSixCorners(tileCoord[0], tileCoord[1]) };
		for (auto corner : corners) {
			for (Player& player : players) {
				if (player.hasSettlementAtCoord(corner[0], corner[1], corner[2])) {
					player.addResource(res, NUMRESSET);
				}
				if (player.hasCityAtCoord(corner[0], corner[1], corner[2])) {
					player.addResource(res, NUMRESCITY);
				}
			}
		}
	}
}