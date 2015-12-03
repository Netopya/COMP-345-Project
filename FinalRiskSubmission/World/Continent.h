#ifndef CONTINENT_H
#define CONTINENT_H

#include <iostream>
#include <string>

using namespace std;
/*
* Holds the name and a unique value for every continent of the map.
*/
class Continent
{
	string name;
	int registryValue;
	int controlValue;

public:
	Continent(string, int, int);
	string getName();
	int getRegistryValue();
	int getControlValue();
};
#endif