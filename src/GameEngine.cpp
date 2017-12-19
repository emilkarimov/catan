/// \file
/// GameEngine.cpp
/// GameEngine class member-function definitions.

#include "GameEngine.h" // Robber class definition
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


// retrieve players on a tile
std::vector <Player> GameEngine::getPlayersOnTile(int x, int y) {
	vector <Player> matchingPlayers;
	array <int, 2> tileinfocus;
	tileinfocus[0] = x;
	tileinfocus[1] = y;

	for (vector<Player>::iterator counterof_players = players.begin(); counterof_players != players.end(); counterof_players++) {
		vector<Settlement> listof_settlements = counterof_players->getSettlements();
		vector<City> listof_cities = counterof_players->getCities();

		for (vector<Settlement>::iterator counterof_settlements = listof_settlements.begin(); counterof_settlements != listof_settlements.end(); counterof_settlements++) {
			if (tileinfocus[0] == counterof_settlements->getLoc()[0] && tileinfocus[1] == counterof_settlements->getLoc()[1])
				matchingPlayers.push_back(*counterof_players);
			else {
				for (vector<City>::iterator counterof_cities = listof_cities.begin(); counterof_cities != listof_cities.end(); counterof_cities++) {
					if (tileinfocus[0] == counterof_cities->getLoc()[0] && tileinfocus[1] == counterof_cities->getLoc()[1])
						matchingPlayers.push_back(*counterof_players);
					else;
				}
			}
		}
	}

	return matchingPlayers;
}


// handle robber function that is called when dice roll result is 7 or Knight card is played
// move the robber, then randomly draw a resource card from the player on the new tile and add it to the player in turn
void GameEngine::handleRobber(Robber& robber, Player& player) {
	// set location of the robber
	std::array <int, 2> newLoc;
	cout << "enter new tile coordinates for the robber:";
	cin >> newLoc[0] >> newLoc[1];

	// check that new location is different than the old one
	std::array <int, 2> oldLoc;
	oldLoc = robber.getLoc();
	while (newLoc[0] == oldLoc[0] && newLoc[1] == oldLoc[1]) {
		cout << "same location is not allowed, enter different coordinates:";
		cin >> newLoc[0] >> newLoc[1];
	}

	// set the location using new coordinates
	robber.setLoc(newLoc[0], newLoc[1]); 
	
	// retrieve players on the new tile
	vector <Player> players_on_tile = getPlayersOnTile(newLoc[0], newLoc[1]);
	//act based on the vector size
	if (players_on_tile.capacity() == 0) {
		cout << "no players on the tile chosen. nothing to do" << endl;
	}
	else if (players_on_tile.capacity() == 1) {
		//random index draw
		//players_on_tile[0].removeResource();
		//player.addResource();
	}
	else {
		// more than 1 player on the tile, pick one
		int index;
		cout << "more than 1 player on the tile, pick one (0, 1, etc):";
		cin >> index;
		//players_on_tile[index].removeResource();
		//player.addResource();
	}
}