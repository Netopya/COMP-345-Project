#include "Country.h"

Country::Country(string name, string continent)
{
	this->name = name;
	this->continent = continent;
	numArmies = rand() % 10; // Randomly assign a number of armies
}

void Country::setControllingPlayer(Player * const & player)
{
	owner = player;
}

void Country::addAdjecentCountry(Country * const & country)
{
	adjacentCountries.push_back(country);
}

vector<Country*> Country::getAdjacentCountries()
{
	return adjacentCountries;
}

string Country::getName() const
{
	return name;
}

string Country::getOwnerName() const
{
	return owner->GetPlayerName();
}

string Country::getOwnerName(int max) const
{
	return owner->GetPlayerName(max);
}

Player * Country::getOwner()
{
	return owner;
}

int Country::getNumArmies() const
{
	return numArmies;
}

string Country::getContinent() const
{
	return continent;
}
