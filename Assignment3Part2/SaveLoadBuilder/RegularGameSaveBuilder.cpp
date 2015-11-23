#include "RegularSaveGameBuilder.h"
#include "Player\Player.h"
#include "World\World.h"
#include "World\Country.h"


RegularSaveGameBuilder::RegularSaveGameBuilder(World* map, vector<Player*>* players, Player* playerTurn, string phase)
{
	this->map = map;
	this->players = players;
	this->playerTurn = playerTurn;
	this->phase = phase;
}

void RegularSaveGameBuilder::initializeSaveLoad()
{
	file.open("example.txt");
}

void RegularSaveGameBuilder::buildPlayers()
{
	file << PLAYERID.c_str() << ' ' << players->size() << endl;

	for (unsigned i = 0; i < players->size(); i++)
	{
		file << players->at(i)->GetPlayerName() << ' ' << endl;
	}
}

void RegularSaveGameBuilder::buildGameState()
{
	file << GAMEID.c_str() << ' ' << playerTurn->GetPlayerName() << ' ' << phase << endl;
}

void RegularSaveGameBuilder::buildWorld()
{
	vector<Country*> countries = *(map->getCountries());

	file << WORLDID << ' ' << countries.size() << endl;

	for (unsigned i = 0; i < countries.size(); i++)
	{
		file << countries[i]->getName() << ' ' << countries[i]->getControllingPlayer()->GetPlayerName() << ' ' << countries[i]->getNumArmies() << endl;
	}
}

void RegularSaveGameBuilder::endSaveLoad()
{
	file.close();
}