#ifndef CONTINENT_H
#define CONTINENT_H
/*
 * Holds the name and a unique value for every continent of the map.
 */
class Continent
{	
	const char* name;
	int registryValue;

public:
	Continent(const char*, int);
	const char* getName();
	int getRegistryValue();
};
#endif