#include "Map.h"

void Map::addCountry(Country * const & country)
{
	countries.push_back(country);
}

const vector<Country*> Map::GetCountries() const
{
	return countries;
}

Country * Map::getCountryByName(string name) const
{
	// Search for a country with the requested name

	for (unsigned i = 0; i < countries.size(); i++)
	{
		if (countries[i]->getName() == name)
		{
			return countries[i];
		}
	}
	
	return nullptr;
}
