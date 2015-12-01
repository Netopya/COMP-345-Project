#include "Country.h"

Country::Country(const char* _name, int _registryValue)
{
	connectedCountries = new vector<Country*>();
	//Cartesian position of the location of the middle pixel of this specific country.
	positionX = 0;
	positionY = 0;
	continent = NULL;
	name = _name;
	registryValue = _registryValue;
	numArmies = 1;
}
void Country::setCartesian(int _positionX, int _positionY)
{
	positionX = _positionX;
	positionY = _positionY;
}
void Country::setContinent(Continent* _continent)
{
	continent = _continent;
}
const char* Country::getName()
{
	return name;
}
vector<Country*>* Country::getConnectedCountries()
{
	return connectedCountries;
}
Continent* Country::getContinent()
{
	return continent;
}
int Country::getRegistryValue()
{
	return registryValue;
}
int Country::getPositionX()
{
	return positionX;
}
int Country::getPositionY()
{
	return positionY;
}
/*
* Links this country to a list of other countries that are
* sent using a vector.
*/
void Country::connect(vector<Country*>* _connections)
{
	for (int i = 0; i < _connections->size(); i++)
	{
		connectedCountries->push_back(_connections->at(i));
	}
}
/*
* Links this country to another country.
*/
void Country::connect(Country* _connection)
{
	connectedCountries->push_back(_connection);
}

void Country::setControllingPlayer(Player* player)
{
	this->owner = player;
}

Player* Country::getControllingPlayer() const
{
	return owner;
}

int Country::getNumArmies()
{
	return numArmies;
}

void Country::addArmies(int armies)
{
	numArmies += armies;
}

void Country::removeArmies(int armies)
{
	numArmies -= armies;
}