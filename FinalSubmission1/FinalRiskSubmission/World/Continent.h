#ifndef CONTINENT_H
#define CONTINENT_H
/*
 * Holds the name and a unique value for every continent of the map.
 */
class Continent
{	
	const char* name;
	int registryValue;
	int controlValue;

public:
	Continent(const char*, int, int);
	const char* getName();
	int getRegistryValue();
	int getControlValue();
};
#endif