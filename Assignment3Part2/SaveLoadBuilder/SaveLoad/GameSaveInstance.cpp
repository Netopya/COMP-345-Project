#include "GameSaveInstance.h"
#include "../Player/Player.h"
#include "../PlayerView/PlayerView.h"

Player * GameSaveInstance::getPlayerByName(string playerName)
{
	for (unsigned i = 0; i < newPlayers->size(); i++)
	{
		if (newPlayers->at(i)->GetPlayerName() == playerName)
		{
			return newPlayers->at(i);
		}
	}

	return NULL;
}

void GameSaveInstance::addCountryInfo(string countryName, string owningPlayer, int numArmies)
{
	CountryInfo* countryInfo = new CountryInfo(countryName, owningPlayer, numArmies);

	countryInfos.push_back(countryInfo);
}

void GameSaveInstance::addArmiesAndPlayersToMap(World * map)
{
	for (unsigned i = 0; i < countryInfos.size(); i++)
	{
		Country* country = map->getCountryFromName(countryInfos[i]->countryName.c_str());

		country->setControllingPlayer(getPlayerByName(countryInfos[i]->owningPlayer));
	}
}

vector<Player*>* GameSaveInstance::createPlayers(World * map)
{
	newPlayers = new vector<class Player*>();
	for (unsigned i = 0; i < players.size(); i++)
	{
		Player* newPlayer = new Player(players[i], map);
		PlayerView* playerview = new PlayerView(newPlayer);
		newPlayers->push_back(newPlayer);
	}
	
	return newPlayers;
}

