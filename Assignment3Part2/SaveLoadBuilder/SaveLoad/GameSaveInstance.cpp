#include "GameSaveInstance.h"
#include "../Player/Player.h"
#include "../PlayerView/PlayerView.h"

Player * GameSaveInstance::getPlayerByName(string playerName)
{
	// Find a newly created player by their name
	for (unsigned i = 0; i < newPlayers->size(); i++)
	{
		if (newPlayers->at(i)->GetPlayerName() == playerName)
		{
			return newPlayers->at(i);
		}
	}

	return NULL;
}

GameSaveInstance::GameSaveInstance()
{
	hasError = false;
}

void GameSaveInstance::addCountryInfo(string countryName, string owningPlayer, int numArmies)
{
	CountryInfo* countryInfo = new CountryInfo(countryName, owningPlayer, numArmies);

	countryInfos.push_back(countryInfo);
}

void GameSaveInstance::addArmiesAndPlayersToMap(World * map)
{
	// Go through the map, assign players to countries they control and set the number of armies
	for (unsigned i = 0; i < countryInfos.size(); i++)
	{
		Country* country = map->getCountryFromName(countryInfos[i]->countryName.c_str());

		if (country == NULL)
		{
			setError(true, "Could not find saved country on map");
			return;
		}

		country->setControllingPlayer(getPlayerByName(countryInfos[i]->owningPlayer));

		country->addArmies(countryInfos[i]->numArmies);
	}
}

vector<Player*>* GameSaveInstance::createPlayers(World * map)
{
	// Create players and their observers
	newPlayers = new vector<class Player*>();
	for (unsigned i = 0; i < players.size(); i++)
	{
		Player* newPlayer = new Player(players[i], map);
		PlayerView* playerview = new PlayerView(newPlayer);
		newPlayers->push_back(newPlayer);
	}
	
	return newPlayers;
}

string GameSaveInstance::getPhase()
{
	return phase;
}

void GameSaveInstance::setError(bool error, string description)
{
	lastError = description;
	hasError = error;
}

bool GameSaveInstance::errorOccured()
{
	return hasError;
}

string GameSaveInstance::getLastError()
{
	return lastError;
}

