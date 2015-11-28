#include "RegularSaveGameBuilder.h"
#include "..\Player\Player.h"
#include "..\World\World.h"
#include "..\World\Country.h"


RegularSaveGameBuilder::RegularSaveGameBuilder(World* map, vector<Player*>* players, Player* playerTurn, string phase)
{
	this->map = map;
	this->players = players;
	this->playerTurn = playerTurn;
	this->phase = phase;
}

void RegularSaveGameBuilder::initializeSaveLoad()
{
	file.open("gamesave.save");
}

void RegularSaveGameBuilder::buildPlayers()
{
	// Write the number of players
	file << PLAYERID.c_str() << ' ' << players->size() << endl;

	// Write the names of the players
	for (unsigned i = 0; i < players->size(); i++)
	{
		file << players->at(i)->GetPlayerName() << ' ' << endl;
	}
}

void RegularSaveGameBuilder::buildGameState()
{
	// Write the current game phase
	file << GAMEID.c_str() << ' ' << playerTurn->GetPlayerName() << ' ' << phase << endl;
}

void RegularSaveGameBuilder::buildWorld()
{
	vector<Country*> countries = *(map->getCountries());

	// Write the number of countries
	file << WORLDID << ' ' << countries.size() << endl;

	// Write the name of each country, the player that controls it, and the number of armies on the country
	for (unsigned i = 0; i < countries.size(); i++)
	{
		file << countries[i]->getName() << ' ' << countries[i]->getControllingPlayer()->GetPlayerName() << ' ' << countries[i]->getNumArmies() << endl;
	}
}

void RegularSaveGameBuilder::endSaveLoad()
{
	file.close();
}