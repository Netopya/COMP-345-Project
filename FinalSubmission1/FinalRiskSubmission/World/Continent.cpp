#include "Continent.h"

Continent::Continent(const char* _name, int _registryValue, int _controlValue)
{
	name = _name;
	registryValue = _registryValue;
	controlValue = _controlValue;
}
const char* Continent::getName()
{
	return name;
}
int Continent::getRegistryValue()
{
	return registryValue;
}

int Continent::getControlValue()
{
	return controlValue;
}
