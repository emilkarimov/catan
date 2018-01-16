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
#include "DevCardDeck.h"
#include <SDL.h>

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

	/// checks if a road is available for building a new road
	bool roadAvailable(int x, int y, TileEdge edge);

	/// roll dice and continue based on 
	unsigned int rollDice();

	/// distribute resources depending on the rolled dice number
	void distributeResources(unsigned int diceNum);

	/// what to do after rolling dice depending on the number rolles
	void handleRollDice(Player& player);

	/// handle settlement building
	void handleBuildSettlement(Player& player);

	/// handle city building
	void handleBuildCity(Player& player);

	/// handle road building
	void handleBuildRoad(Player& player);

	/// handle robber function that is called when dice roll result is 7 or Knight card is played
	void handleRobber(Player& player);

	/// retrieve players on a tile
	bool playersOnTile(Player& p, int x, int y);

	/// play a dev card
	void GameEngine::playDevCard(Player& player);

	/// update special cards and its owners
	void GameEngine::updateSpecialCards();

	/// player trading with bank
	void GameEngine::tradeBank(Player& player);

	/// player to player trading 
	void playerTrading(Player& player);

	/// check whether a player wants to place a settlement into the sea
	bool putInSea(int x, int y, TileIntersection z);

	/// discard resources when 7 is rolled and a player has >= 8 cards
	void discardResources();

	/// draw
	void testSDLGE();

	/// draw tiles

	void drawTile(SDL_Renderer* renderer, Tile& tile);

	void drawRoad(SDL_Renderer* renderer, const Road& road, std::string color);

	void drawSettlement(SDL_Renderer* renderer, const Settlement& settlement, std::string color);

	void drawCity(SDL_Renderer* renderer, const City& city, std::string color);

	void drawRobber(SDL_Renderer* renderer, Robber& robber);

	void drawUpdate();

	void drawNum(SDL_Renderer* renderer, int x, int y, int num);

	void drawCircle(SDL_Renderer* renderer, int x, int y, int r);
	void drawFilledCircle(SDL_Renderer* renderer, int x, int y, int r);
private:
	std::vector<Player> players;
	Board board;
	Robber robber;
	DevCardDeck deck;
	SDL_Renderer* renderer;
	SDL_Window* window;


};

#endif // GAMEENGINE_H


