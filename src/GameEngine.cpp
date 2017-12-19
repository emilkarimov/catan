/// \file
/// GameEngine.cpp
/// GameEngine class member-function definitions.

#include "GameEngine.h" // Robber class definition
#include "DevCardDeck.h"
#include <iostream>
#include <string>
using namespace std;



// constructor 
GameEngine::GameEngine(std::vector<Player> players, std::vector<Tile> tiles)
	: players(players), tiles(tiles) {

}

// start game
void GameEngine::start() {

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
		bool devcardplayed{ false };
		while (NotLegalMove) {
			cin >> moveInput;
			if (moveInput == "1") {
				cout << "roll dice" << "\n";
				NotLegalMove = false;
			}
			else if (moveInput == "2" && player.canPlayDev()) {
				cout << "Play development card" << "\n";
				playDevCard(player);
				devcardplayed = true;
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
	std::array<int, 3> settlementLoc = player.getSettlements()[1].getLoc();
	cout << settlementLoc[0] << " " << settlementLoc[1] << " " << settlementLoc[2] << "\n";
	Tile* tile1Ptr = findTile(settlementLoc[0], settlementLoc[1]);
	cout << tile1Ptr->toString() << "\n";
	player.addResource(tile1Ptr->produces(), 1);

	// resources from two upper tiles
	if (settlementLoc[2] == TOP) {
		// upper right tile resource addition
		std::array<int, 2> neighbor1Coord{ tile1Ptr->getNeighborCoord(1) };
		cout << "neighbor1 coord: " << neighbor1Coord[0] << " " << neighbor1Coord[1] << "\n";
		Tile* neighbor1TilePtr = findTile(neighbor1Coord[0], neighbor1Coord[1]);
		player.addResource(neighbor1TilePtr->produces(), 1);

		// upper left tile resource addition
		std::array<int, 2> neighbor6Coord{ tile1Ptr->getNeighborCoord(6) };
		cout << "neighbor6 coord: " << neighbor6Coord[0] << " " << neighbor6Coord[1] << "\n";
		Tile* neighbor6TilePtr = findTile(neighbor6Coord[0], neighbor6Coord[1]);
		player.addResource(neighbor6TilePtr->produces(), 1);
	}

	// resources from two lower tiles
	if (settlementLoc[2] == BOTTOM) {
		// lower right tile resource addition
		std::array<int, 2> neighbor3Coord{ tile1Ptr->getNeighborCoord(3) };
		cout << "neighbor3 coord: " << neighbor3Coord[0] << " " << neighbor3Coord[1] << "\n";
		Tile* neighbor3TilePtr = findTile(neighbor3Coord[0], neighbor3Coord[1]);
		player.addResource(neighbor3TilePtr->produces(), 1);

		// lower left tile resource addition
		std::array<int, 2> neighbor4Coord{ tile1Ptr->getNeighborCoord(4) };
		cout << "neighbor4 coord: " << neighbor4Coord[0] << " " << neighbor4Coord[1] << "\n";
		Tile* neighbor4TilePtr = findTile(neighbor4Coord[0], neighbor4Coord[1]);
		player.addResource(neighbor4TilePtr->produces(), 1);
	}
}

// find tile with specific x y coordinates and return the reference
Tile* GameEngine::findTile(int x, int y) {
	for (Tile& tileRef : tiles) {
		if (tileRef.getCoord()[0] == x && tileRef.getCoord()[1] == y) {
			return &tileRef;
		}
	}
	return nullptr; // return tilePtr if the coordinates are not correct
}




// play development card
void GameEngine::playDevCard(Player& player) {
	int choise{ 0 };
	vector<DevelopmentCard> cards = player.returnDevcards();
	cout << "Which development card would you like to play:\n";
	for (int index = 0; index < cards.size(); ++index) {
		if (cards[index].getType() == VICTORY) {
			cout << "   VICTORY";
		}
		else {
			string type = cards[index].toString();
			cout << index+1 << "  " << type << endl;
		}
	}
	cin >> choise;
	Devtype chosentype = cards[choise-1].getType();
	string z;
	string type1, type2;
	switch (chosentype) {
	case KNIGHT:
		///handlerobber();
		cout << "played a knight card";
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
		break;
	case YEAROFPLENTY:
		cout << "identify 2 resources that you want to add:\n";
		cin >> type2 >> type2;
		for (int i = 0; i < 1; ++i) {
			if (type1 == "GRAIN") {
				player.addResource(GRAIN, 1);
			}
			if (type1 == "BRICK") {
				player.addResource(BRICK, 1);
			}
			if (type1 == "WOOL") {
				player.addResource(WOOL, 1);
			}
			if (type1 == "LUMBER") {
				player.addResource(LUMBER, 1);
			}
			if (type1 == "ORE") {
				player.addResource(ORE, 1);
			}
			type1 = type2;
		}
		break;
	case MONOPOLY:
		cout << "what type of reasource would you like to take";
		cin >> z;
		if (z == "GRAIN") {
			for (auto e : players) {
				if (e.getName() == player.getName()) {
					break;
				}
				else {
					player.addResource(GRAIN, e.getNumGrain());
					e.removeResource(GRAIN, e.getNumGrain());
				}
			}
		}
		if (z == "BRICK") {
			for (auto e : players) {
				if (e.getName() == player.getName()) {
					break;
				}
				else {
					player.addResource(BRICK, e.getNumGrain());
					e.removeResource(BRICK, e.getNumGrain());
				}
			}
		}
		if (z == "WOOL") {
			for (auto e : players) {
				if (e.getName() == player.getName()) {
					break;
				}
				else {
					player.addResource(WOOL, e.getNumGrain());
					e.removeResource(WOOL, e.getNumGrain());
				}
			}
		}
		if (z == "LUMBER") {
			for (auto e : players) {
				if (e.getName() == player.getName()) {
					break;
				}
				else {
					player.addResource(GRAIN, e.getNumGrain());
					e.removeResource(GRAIN, e.getNumGrain());
				}
			}
		}
		if (z == "ORE") {
			for (auto e : players) {
				if (e.getName() == player.getName()) {
					break;
				}
				else {
					player.addResource(GRAIN, e.getNumGrain());
					e.removeResource(GRAIN, e.getNumGrain());
				}
			}
		}
		break;
	}
	player.removeDevCard(chosentype);
}

void GameEngine::updateSpecialCards() {
	for (auto p : players) {
		if (p.hasLargestArmy()) {
			Player currentowner = p;
			for (auto p : players) {
				if (p.getNumKnightcards() > currentowner.getNumKnightcards()) {
					p.addspecialCard(LARGESTARMY);
					currentowner.removespecialCard(LARGESTARMY);
				}
			}
			break;
		}
	}
	
}