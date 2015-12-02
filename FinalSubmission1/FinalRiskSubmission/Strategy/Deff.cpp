#pragma once

#include "Deff.h"

string Deff::executeSource(std::vector<Country*>  occupied)
{
	bool sourceCountry = true;

	//int playerID = countryList[occupied[0]].getMPlayer();
	Player* playerID = occupied[0]->getControllingPlayer();
	for (int i = 0; i < occupied.size(); i++)
	{
		vector<Country*> adjacentCountries(*(occupied[i]->getConnectedCountries()));
		for (int j = 0; j < adjacentCountries.size(); j++)
		{
			Country* tempTarget;
			tempTarget = adjacentCountries[j];

			// checks if selected country contained more armies then all neighbour contries in the loop.
			if (tempTarget->getControllingPlayer() != playerID)
				sourceCountry = sourceCountry && (tempTarget->getNumArmies() < occupied[i]->getNumArmies() - 1);
		}
		if (sourceCountry)
		{
			if (occupied[i]->getNumArmies() >= 2) {  // check if selected country is valid;
				return occupied[i]->getName();
				break;
			}
		}
	}
	std::cout << "Attack phase ended" << std::endl;
	return "0";
}
string Deff::executeTarget(Country* sourceCountry)
{
	//int playerID = countryList[sourceCountry].getMPlayer();
	Player* playerID = sourceCountry->getControllingPlayer();
	Country* minIndex = 0;
	int minIndexDif = 0;
	vector<Country*> adjacentCountries(*(sourceCountry->getConnectedCountries()));
	for (int i = 1; i < adjacentCountries.size(); i++)
	{
		if (playerID != adjacentCountries[i]->getControllingPlayer()) {
			if (adjacentCountries[i]->getNumArmies() < sourceCountry->getNumArmies())
			{
				if (sourceCountry->getNumArmies() - adjacentCountries[i]->getNumArmies() > minIndexDif) {
					minIndex = adjacentCountries[i];
					minIndexDif = sourceCountry->getNumArmies() - adjacentCountries[i]->getNumArmies();
				}
			}
		}
	}
	return minIndex->getName();
}

string Deff::getID()
{
	return DEFFID;
}

