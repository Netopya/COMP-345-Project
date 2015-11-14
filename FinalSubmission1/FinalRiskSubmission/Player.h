#pragma once

/*
Player in the game, they have a name, an alive status, and a number of wins along with methods to determine controlled armies, countries, and continents
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
	vector<class Country*> getCountries(); // Get controlled countries
	vector<class Continent*> getContinents(); // Get controlled continents
};