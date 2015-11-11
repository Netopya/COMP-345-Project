#pragma once

/*
Michael Bilinsky 26992358
COMP 345 Assignment #2 - Part 2: Map Observer Pattern

Player in the game, they have a name and an alive status
*/

#include <string>
#include <vector>

#include "MyObservable.h"

using namespace std;

class Player : public MyObservable {

private:
	string playerName;
	bool alive;
	class World* map;
	int wins;
public:
	Player(string, class World*);
	string GetPlayerName();
	string GetPlayerName(int); // Get the player's name truncated to a max length
	const bool isAlive();
	void kill();
	int getNumArmies();
	int getNumWins() const;
	void addWin();
	vector<class Country*> getCountries();
	vector<class Continent*> getContinents();
};