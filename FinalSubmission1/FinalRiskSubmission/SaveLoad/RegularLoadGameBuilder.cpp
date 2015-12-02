#include <string>
#include "RegularLoadGameBuilder.h"

void RegularLoadGameBuilder::initializeSaveLoad()
{
	// Open the game save file
	file.open("gamesave.save", ios::in);
	saveInstance = new GameSaveInstance();

	if (!file.is_open())
	{
		saveInstance->setError(true, "Could not open save file, have you saved a game yet?");
	}
}

void RegularLoadGameBuilder::buildPlayers()
{
	// read the players from the save file

	string playerInfo;
	int numPlayers;
	int soldiers;
	int cavalry;
	int artillery;
	int cardBonus;
	file >> playerInfo >> numPlayers >> soldiers >> cavalry >> artillery >> cardBonus;

	if (playerInfo == PLAYERID)
	{
		for (int i = 0; i < numPlayers; i++)
		{
			string playerName;
			bool isAI;
			file >> playerName >> isAI;

			saveInstance->addPlayerInfo(decodeString(playerName), isAI, soldiers, cavalry, artillery, cardBonus);
		}
	}
	else
	{
		saveInstance->setError(true, "Could not parse player info from saved game");
	}
}

void RegularLoadGameBuilder::buildGameState()
{
	// read the game state saved in the file

	string stateInfo;
	string playerTurn;
	file >> stateInfo >> playerTurn >> saveInstance->phase;

	if (stateInfo != GAMEID)
	{
		saveInstance->setError(true, "Could not parse game state from saved game");
	}
	else
	{
		saveInstance->playerTurn = decodeString(playerTurn);
	}
}

void RegularLoadGameBuilder::buildWorld()
{
	// read the saved world information from the file

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
			saveInstance->addCountryInfo(decodeString(countryName), decodeString(playerName), numArmies);
		}
	}
	else
	{
		saveInstance->setError(true, "Could not parse world info from saved game");
	}

}

void RegularLoadGameBuilder::endSaveLoad()
{
	file.close();
}
