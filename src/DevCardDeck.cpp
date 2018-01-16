/// \file
/// DevCardDeck.cpp
/// DevelopmentCarddeck class member-function definitions.
#include "DevelopmentCard.h" // Card class definition
#include "DevCardDeck.h"
#include <iostream>
#include <vector>
#include "Player.h"
#include "time.h"
using namespace std;

// string info
string DevCardDeck::toString() const {
	cout << "The deck currently contains:\n";
	for (auto e: deck) {
		string type = e.toString();
		cout << type << endl;
	}
	return "development card deck";
}

// draw function
void DevCardDeck::draw() const {
	cout << "draw development card\n";
}

// buy dev card. Gives a new dev card to player, removes resources from player
void DevCardDeck::buyDevelopmentCard(Player& player) {
	if (player.getNumGrain() < 1 && player.getNumWool() < 1 && player.getNumOre() < 1) {
		cout << "insufficient resources\n";
		return;
	}
	int range = deck.size();
	srand(time(NULL));
	int index = rand() % range;
	Devtype type = deck[index].getType();
	deck.erase(deck.begin() + index);
	player.addDevCard(type);
	player.removeResource(WOOL, 1);
	player.removeResource(GRAIN, 1);
	player.removeResource(ORE, 1);
}

// add dev card to the deck
void DevCardDeck::addDevelopmentCard(Devtype type) {
	deck.push_back(DevelopmentCard(type));
}

// initialization
void DevCardDeck::initDeck() {
	for (int i = 0; i < 14; i++) {
		addDevelopmentCard(KNIGHT);
	}
	for (int i = 0; i < 2; i++) {
		addDevelopmentCard(ROADBUILDING);
	}
	for (int i = 0; i < 2; i++) {
		addDevelopmentCard(YEAROFPLENTY);
	}
	for (int i = 0; i < 2; i++) {
		addDevelopmentCard(MONOPOLY);
	}
	for (int i = 0; i < 5; i++) {
		addDevelopmentCard(VICTORY);
	}	
}