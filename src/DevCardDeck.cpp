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

string DevCardDeck::toString() const {
	cout << "The deck currently contains:\n";
	for (auto e: deck) {
		string type = e.toString();
		cout << type << endl;
	}
	return "development card deck";
}

void DevCardDeck::draw() const {
	cout << "draw development card\n";
}


void DevCardDeck::buyDevelopmentCard(Player& player) {
	int range = deck.size();
	srand(time(NULL));
	int index = rand() % range;
	Devtype type = deck[index + 1].getType();
	deck.erase(deck.begin() + index);
	player.addDevCard(type);
	player.removeResource(WOOL, 1);
	player.removeResource(GRAIN, 1);
	player.removeResource(ORE, 1);
}

void DevCardDeck::addDevelopmentCard(Devtype type) {
	deck.push_back(DevelopmentCard(type));
}

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