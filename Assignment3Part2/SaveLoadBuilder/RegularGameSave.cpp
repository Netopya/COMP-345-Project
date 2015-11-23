#include "RegularSaveGame.h"
#include "Player\Player.h"
#include "World\World.h"
#include "World\Country.h"


RegularSaveGame::RegularSaveGame(World* map, vector<Player*>* players, Player* playerTurn, string phase)
{
	this->map = map;
	this->players = players;
	this->playerTurn = playerTurn;
	this->phase = phase;
}

void RegularSaveGame::initializeSaveLoad()
{
	file.open("example.txt");
}

void RegularSaveGame::buildPlayers()
{
	file << PLAYERID.c_str() << ' ' << players->size() << endl;

	for (unsigned i = 0; i < players->size(); i++)
	{
		file << players->at(i)->GetPlayerName() << ' ' << endl;
	}
}

void RegularSaveGame::buildGameState()
{
	file << GAMEID.c_str() << ' ' << playerTurn->GetPlayerName() << ' ' << phase << endl;
}

void RegularSaveGame::buildWorld()
{
	vector<Country*> countries = *(map->getCountries());

	file << WORLDID << ' ' << countries.size() << endl;

	for (unsigned i = 0; i < countries.size(); i++)
	{
		file << countries[i]->getName() << ' ' << countries[i]->getControllingPlayer()->GetPlayerName() << ' ' << countries[i]->getNumArmies() << endl;
	}
}

void RegularSaveGame::endSaveLoad()
{
	file.close();
}