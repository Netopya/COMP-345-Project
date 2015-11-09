#pragma once

#include <vector>
#include "Player.h"
using namespace std;

/*
Michael Bilinsky 26992358
COMP 345 Assignment #2 - Part 2: Map Observer Pattern

Countries piece of the game, they have a name, owing player, number of armies, and a list of adjacent countries
*/

class Country {
private:
	vector<Country*> adjacentCountries;
	string name;
	string continent;
	Player* owner;
	int numArmies;
public:
	Country(string name, string continent);
	void setControllingPlayer(Player* const & player); // Assign a new owner
	void addAdjecentCountry(Country* const& country);
	vector<Country*> getAdjacentCountries();
	string getName() const;
	string getOwnerName() const;
	string getOwnerName(int) const; // Get the owner truncated at a max length
	Player* getOwner();
	int getNumArmies() const;
	string getContinent() const;
};