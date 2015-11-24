#include <string>
#include "RegularLoadGameBuilder.h"

void RegularLoadGameBuilder::initializeSaveLoad()
{
	file.open("example.txt", ios::in);
	saveInstance = new GameSaveInstance();
}

void RegularLoadGameBuilder::buildPlayers()
{
	string playerInfo;
	int numPlayers;
	file >> playerInfo >> numPlayers;

	if (playerInfo == PLAYERID)
	{
		for (int i = 0; i < numPlayers; i++)
		{
			string playerName;
			file >> playerName;

			saveInstance->players.push_back(playerName);
		}
	}
}

void RegularLoadGameBuilder::buildGameState()
{
	string stateInfo;
	file >> stateInfo >> saveInstance->playerTurn >> saveInstance->phase;

	if (stateInfo == GAMEID)
	{
		//no error
	}
}

void RegularLoadGameBuilder::buildWorld()
{
	string worldInfo;
	int numCountries;
	file >> worldInfo >> numCountries;

	if (worldInfo == WORLDID)
	{
		for (int i = 0; i < numCountries; i++)
		{
			string countryName;
			string playerName;
			int numArmies;
			file >> countryName >> playerName >> numArmies;
			saveInstance->addCountryInfo(countryName, playerName, numArmies);
		}
	}

}

void RegularLoadGameBuilder::endSaveLoad()
{
	file.close();
}
