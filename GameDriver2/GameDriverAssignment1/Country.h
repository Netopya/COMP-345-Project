#pragma once

#include <string>

using namespace std;

class Country {
private:
	string countryName;
public:
	Country(string);
	string GetCountryName();
};