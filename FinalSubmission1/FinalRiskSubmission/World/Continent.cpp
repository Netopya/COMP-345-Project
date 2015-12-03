#include "Continent.h"

Continent::Continent(string _name, int _registryValue, int _controlValue)
{
	name = _name;
	registryValue = _registryValue;
	controlValue = _controlValue;
}
int Continent::getControlValue()
{
	return controlValue;
}
string Continent::getName()
{
	return name;
}
int Continent::getRegistryValue()
{
	return registryValue;
}