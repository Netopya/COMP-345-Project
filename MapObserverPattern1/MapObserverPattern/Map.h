#pragma once

/*
Michael Bilinsky 26992358
COMP 345 Assignment #2 - Part 2: Map Observer Pattern

The game's map, holds a list of all the countries
*/

#include "MyObservable.h"
#include "Country.h"
class Map : public MyObservable
{
	vector<Country*> countries;
public:
	void addCountry(Country* const& country);
	const vector<Country*> GetCountries() const;
	Country* getCountryByName(string name) const;
};
