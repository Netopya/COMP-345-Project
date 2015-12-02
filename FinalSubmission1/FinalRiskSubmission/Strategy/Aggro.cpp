#pragma once

#include "Aggro.h"

string Aggro::executeSource(std::vector<Country*>  occupied)
{
	Player* playerID = occupied[0]->getControllingPlayer();
	bool sourceCountry = true;
	for (int i = 0; i < occupied.size(); i++)
	{
		vector<Country*> adjacentCountries(*(occupied[i]->getConnectedCountries()));
		for (int j = 0; j < adjacentCountries.size(); j++)
		{
			Country* tempTarget;
			tempTarget = adjacentCountries[j];
			if (tempTarget->getControllingPlayer() != playerID)
				sourceCountry = (tempTarget->getNumArmies() < occupied[i]->getNumArmies());

			if (sourceCountry)
			{
				if (occupied[i]->getNumArmies() >= 2) {
					return occupied[i]->getName();
					break;
				}
			}
		}
	}
	std::cout << "Attack phase ended" << std::endl;
	return "0";
}
string Aggro::executeTarget(Country* sourceCountry)
{
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

string Aggro::getID()
{
	return AGGROID;
}

