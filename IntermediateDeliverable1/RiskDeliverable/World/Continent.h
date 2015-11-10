#pragma once
/*
 * Holds the name and a unique value for every continent of the map.
 */
class Continent
{	
	const char* name;
	int registryValue;

public:
	Continent(const char* _name, int _registryValue)
	{
		name = _name;
		registryValue = _registryValue;
	}
	const char* getName()
	{
		return name;
	}
	int getRegistryValue()
	{
		return registryValue;
	}
};