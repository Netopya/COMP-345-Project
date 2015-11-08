#include "Country.h"

Country::Country(string name)
{
	this->name = name;
}

void Country::setPlayer(Player * const & player)
{
	owner = player;
}

void Country::addAdjecentCountry(Country * const & country)
{
	adjecentCountries.push_back(country);
}

string Country::getName() const
{
	return name;
}
