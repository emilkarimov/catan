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
#include "Board.h"
#include "Robber.h"

/// GameEngine class
///
/// More detailed text.
class GameEngine {
public:
	/// constructor
	GameEngine(std::vector<Player> players, Board board);

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

	/// checks if a corner is available for placing a settlements
	bool cornerFree(int x, int y, TileIntersection intersec);

	/// distribute resources depending on the rolled dice number
	void distributeResources(unsigned int diceNum);

	/// handle robber function that is called when dice roll result is 7 or Knight card is played
	void handleRobber(Robber& robber, Player& player);

	/// retrieve players on a tile
	bool playersOnTile(Player& p, int x, int y) const;

	/// play development card
	void GameEngine::playDevCard(Player& player, Robber& robber);

	/// update special cards
	void GameEngine::updateSpecialCards();

	void testfunction(Robber& robber);

private:
	std::vector<Player> players;
	Board board;

};

#endif // GAMEENGINE_H


