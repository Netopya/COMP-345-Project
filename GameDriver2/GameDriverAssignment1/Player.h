#pragma once

#include <string>
#include <vector>
#include "Country.h"
using namespace std;

class Player {

private:
	string playerName;
	
	// Countries that the player owns
	vector<Country*> countries;

	// Whether the player is still in the game
	bool alive;

public:
	Player(string);
	string GetPlayerName();
	const vector<Country*> GetCountries();

	// Assign a country to the player
	void AddCountry(Country*);

	// Called when the player is attacked
	void Attack();

	const bool Alive();
};