#include "RegularSaveGameBuilder.h"
#include "..\Player\Player.h"
#include "..\World\World.h"
#include "..\World\Country.h"
#include "..\Strategy\Strategy.h"

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
		Strategy* strat = players->at(i)->getStrategy();
		string stratID = strat == nullptr ? Strategy::NONEID : strat->getID();

		file << encodeString(players->at(i)->GetPlayerName()) << ' ' 
			<< players->at(i)->getNumSoldiers() << ' '
			<< players->at(i)->getNumCavalry() << ' '
			<< players->at(i)->getNumArtillery() << ' '
			<< players->at(i)->getCardBonus() << ' '
			<< stratID
			<< endl;
	}
}

void RegularSaveGameBuilder::buildGameState()
{
	// Write the current game phase
	file << GAMEID.c_str() << ' ' << encodeString(playerTurn->GetPlayerName()) << ' ' << phase << endl;
}

void RegularSaveGameBuilder::buildWorld()
{
	vector<Country*> countries = *(map->getCountries());

	// Write the number of countries
	file << WORLDID << ' ' << countries.size() << endl;

	// Write the name of each country, the player that controls it, and the number of armies on the country
	for (unsigned i = 0; i < countries.size(); i++)
	{
		file << encodeString(countries[i]->getName()) << ' ' << encodeString(countries[i]->getControllingPlayer()->GetPlayerName()) << ' ' << countries[i]->getNumArmies() << endl;
	}
}

void RegularSaveGameBuilder::endSaveLoad()
{
	file.close();
}