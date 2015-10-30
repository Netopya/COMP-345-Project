#include "Country.h"

Country::Country(string countryName)
{
	this->countryName = countryName;
}

string Country::GetCountryName()
{
	return countryName;
}
