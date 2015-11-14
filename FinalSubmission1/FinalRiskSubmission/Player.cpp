#include <iostream>
#include "Player.h"
#include "World\World.h"

using namespace std;

Player::Player(string playerName, World* map)
{
	this->playerName = playerName;
	this->map = map;
	alive = true;
	wins = 0;
}

string Player::GetPlayerName()
{
	return playerName;
}

string Player::GetPlayerName(int max)
{
	return playerName.substr(0, max);
}

const bool Player::isAlive()
{
	return alive;
}

void Player::kill()
{
	alive = false;
}

int Player::getNumArmies()
{
	int armies = 0;
	vector<Country*> countries = getCountries();

	for (unsigned i = 0; i < countries.size(); i++)
	{
		armies += countries[i]->getNumArmies();
	}

	return armies;
}

int Player::getNumWins() const
{
	return wins;
}

void Player::addWin()
{
	wins += 1;
}

vector<Country*> Player::getCountries()
{
	vector<Country*> countries;

	for (unsigned i = 0; i < map->getCountries()->size(); i++)
	{
		if (map->getCountries()->at(i)->getControllingPlayer() == this)
		{
			countries.push_back(map->getCountries()->at(i));
		}
	}

	return countries;
}

vector<Continent*> Player::getContinents()
{
	vector<Continent*> continents;

	for (unsigned i = 0; i < map->getContinents()->size(); i++)
	{
		bool continentOwned = true;
		for (unsigned j = 0; j < map->getCountries()->size(); j++)
		{
			if (map->getCountries()->at(j)->getContinent() == map->getContinents()->at(i) && map->getCountries()->at(j)->getControllingPlayer() != this)
			{
				continentOwned = false; //If the player doesn't control a country on this continent, then they don't control the continent
				break;
			}
		}

		if (continentOwned)
		{
			continents.push_back(map->getContinents()->at(i));
		}
	}

	return continents;
}