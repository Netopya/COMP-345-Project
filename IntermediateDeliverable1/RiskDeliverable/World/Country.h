#pragma once

#include "../Player.h"
/*
 * Holds the name and a unique value for every country of the map.
 * Contains a vector of all the other country it is connected to.
 */
class Country
{
	//Name of the country.
	const char* name;
	//Continent it is hold by.
	class Continent* continent;
	//Unique value.
	int registryValue;
	//Cartesian values.
	int positionX, positionY;
	//Linked countries.
	vector<Country*>* connectedCountries;

	Player* owner;
	int numArmies;

public:
	Country(const char* _name, int _registryValue)
	{
		connectedCountries = new vector<Country*>();
		//Cartesian position of the location of the middle pixel of this specific country.
		positionX = 0;
		positionY = 0;
		continent = NULL;
		name = _name;
		registryValue = _registryValue;
	}
	void setCartesian(int _positionX, int _positionY)
	{
		positionX = _positionX;
		positionY = _positionY;
	}
	void setContinent(Continent* _continent)
	{
		continent = _continent;
	}
	const char* getName()
	{
		return name;
	}
	vector<Country*>* getConnectedCountries()
	{
		return connectedCountries;
	}
    Continent* getContinent()
	{
		return continent;
	}
	int getRegistryValue()
	{
		return registryValue;
	}
	int getPositionX()
	{
		return positionX;
	}
	int getPositionY()
	{
		return positionY;
	}
	/*
	 * Links this country to a list of other countries that are
	 * sent using a vector.
	 */
	void connect(vector<Country*>* _connections)
	{
		for (int i = 0; i < _connections->size(); i++)
		{
			connectedCountries->push_back(_connections->at(i));
		}
	}
	/*
	 * Links this country to another country.
	 */
	void connect(Country* _connection)
	{
		connectedCountries->push_back(_connection);
	}

	void setControllingPlayer(Player* player)
	{
		this->owner = player;
	}

	Player* getControllingPlayer() const
	{
		return owner;
	}

	int getNumArmies() const
	{
		return numArmies;
	}

};