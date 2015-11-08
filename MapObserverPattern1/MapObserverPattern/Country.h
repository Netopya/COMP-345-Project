#pragma once

#include <vector>
#include "Player.h"
using namespace std;

class Country {
private:
	vector<Country*> adjecentCountries;
	string name;
	Player* owner;
public:
	Country(string name);
	void setPlayer(Player* const & player);
	void addAdjecentCountry(Country* const& country);
	string getName() const;
};