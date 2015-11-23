#include "Continent.h"

Continent::Continent(const char* _name, int _registryValue)
{
	name = _name;
	registryValue = _registryValue;
}
const char* Continent::getName()
{
	return name;
}
int Continent::getRegistryValue()
{
	return registryValue;
}