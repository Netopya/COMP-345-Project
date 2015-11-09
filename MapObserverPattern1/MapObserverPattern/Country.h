#pragma once

#include <vector>
#include "Player.h"
using namespace std;

class Country {
private:
	vector<Country*> adjecentCountries;
	string name;
	string continent;
	Player* owner;
	int numArmies;
public:
	Country(string name, string continent);
	void setControllingPlayer(Player* const & player);
	void addAdjecentCountry(Country* const& country);
	vector<Country*> getAdjacentCountries();
	string getName() const;
	string getOwnerName() const;
	string getOwnerName(int) const;
	Player* getOwner();
	int getNumArmies() const;
	string getContinent() const;
};