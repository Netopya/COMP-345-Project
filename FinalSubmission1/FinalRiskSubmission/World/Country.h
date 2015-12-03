#ifndef COUNTRY_H
#define COUNTRY_H

#include <vector>
#include <iostream>
#include <string>
#include "Continent.h"
#include "..\Player\Player.h"

using namespace std;

/*
 * Holds the name and a unique value for every country of the map.
 * Contains a vector of all the other country it is connected to.
 */
class Country
{
	//Name of the country.
	string name;
	//Continent it is hold by.
	Continent* continent;
	//Unique value.
	int registryValue;
	//Cartesian values.
	int positionX, positionY;
	//Linked countries.
	vector<Country*>* connectedCountries;
	//Controlling player.
	class Player* owner;
	//Number of armies.
	int numArmies;

public:
	Country(string _name, int _registryValue);
	void setCartesian(int _positionX, int _positionY);
	void setContinent(Continent* _continent);
	string getName();
	vector<Country*>* getConnectedCountries();
	Continent* getContinent();
	int getRegistryValue();
	int getPositionX();
	int getPositionY();
	/*
	 * Links this country to a list of other countries that are
	 * sent using a vector.
	 */
	void connect(vector<Country*>* _connections);
	/*
	 * Links this country to another country.
	 */
	void connect(Country* _connection);
	void setControllingPlayer(Player* player);

	/*
	 * TODO
	 */
	Player* getControllingPlayer() const;

	int getNumArmies();

	void addArmies(int armies);

	void setArmies(int armies);

	void removeArmies(int armies);

};
#endif