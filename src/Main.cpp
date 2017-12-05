#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <map>
#include <iostream>

#include "Building.h"
#include "City.h"
#include "Settlement.h"
#include "Road.h"
using namespace std;

void rollDice();

int main()
{
	std::cout << "\nbegin\n";
	std::cout << "\nnew road:\n";
	Road road = Road();
	std::cout << road.toString() << "\n";
	std::array<int, 2> roadLoc{ road.getLoc() };
	cout << "location is edge between tiles: " << roadLoc[0] << " " << roadLoc[1] << "\n";
	road.setLoc(2, 3);
	roadLoc = road.getLoc();
	cout << "now location is edge between tiles: " << roadLoc[0] << " " << roadLoc[1] << "\n";
	road.draw();
	rollDice();
	return 0;
}

void rollDice()
{
	int die1, die2;
	for (int i = 0; i < 20; i++)
	die1 = (rand() % 6) + 1;
	die2 = (rand() % 6) + 1;
	cout << die1 << " " << die2 << "\n";
}