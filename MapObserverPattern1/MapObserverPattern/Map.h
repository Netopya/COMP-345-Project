#pragma once

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
