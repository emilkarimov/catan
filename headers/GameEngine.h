/// \file
/// GameEngine.h
/// GameEngine class.

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <string> // C++ standard string class
#include <vector>
#include "Enums.h"
#include "Player.h"
#include "Tile.h"
#include "Robber.h"

/// GameEngine class
///
/// More detailed text.
class GameEngine {
public:
	/// constructor
	GameEngine(std::vector<Player> players, std::vector<Tile> tiles);

	/// destructor
	~GameEngine() = default;

	/// start game
	void start();

	/// 1st stage - players build two settlements and two roads
	void firstStage();

	/// 2nd stage - players take actions in turn
	void secondStage();

	/// possible moves a player can take
	std::string possibleMoves(Player& player, TurnStage stage);

	/// print info about all the players
	void printInfoPlayers();

	/// add initial resources depending on the second settlement
	void addInitResources(Player& player);

	/// find tile with specific x y coordinates and return the reference
	Tile* findTile(int x, int y);

	/// handle robber function that is called when dice roll result is 7 or Knight card is played
	void handleRobber(Robber& robber, Player& player);

	/// retrieve players on a tile
	std::vector <Player> getPlayersOnTile(int x, int y);

private:
	std::vector<Player> players;
	std::vector<Tile> tiles;

};

#endif // GAMEENGINE_H


