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

void GameSaveInstance::addPlayerInfo(string playerName, int soldiers, int cavalry, int artillery, int cardBonus, string strategy)
{
	PlayerInfo* playerInfo = new PlayerInfo(playerName, soldiers, cavalry, artillery, cardBonus, strategy);
	players.push_back(playerInfo);
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

		country->setArmies(countryInfos[i]->numArmies);
	}
}

vector<Player*>* GameSaveInstance::createPlayers(World * map)
{
	// Create players and their observers
	newPlayers = new vector<class Player*>();
	for (unsigned i = 0; i < players.size(); i++)
	{
		Player* newPlayer = new Player(players[i]->playerName, map);
		newPlayer->setCards(players[i]->soldiers, players[i]->cavalry, players[i]->artillery, players[i]->cardBonus);
		PlayerView* playerview = new PlayerView(newPlayer);
		newPlayers->push_back(newPlayer);
	}
	
	return newPlayers;
}

string GameSaveInstance::getPhase()
{
	return phase;
}

string GameSaveInstance::getPlayer()
{
	return playerTurn;
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

