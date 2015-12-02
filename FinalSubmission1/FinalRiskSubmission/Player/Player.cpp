#include "Player.h"

Player::Player(string playerName, World* map, bool ai)
{
	this->playerName = playerName;
	this->map = map;
	computerPlayer = ai;
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

bool Player::isAlive()
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

bool Player::isComputerPlayer() const
{
	return computerPlayer;
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
				continentOwned = false; //If the player doesn't control a country on this continent, then they don't control the continent.
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

void Player::addRandomCard()
{
	int card = rand() % 2;

	switch (card)
	{
	case 0:
		numInfantryCards++;
		cout << GetPlayerName() << " has gained an infantry card" << endl;
		break;
	case 1:
		numCavalryCards++;
		cout << GetPlayerName() << " has gained a cavalry card" << endl;
		break;
	case 2:
		numArtilleryCards++;
		
		cout << GetPlayerName() << " has gained an artillery card" << endl;
		break;
	}
}

int Player::numCards() const
{
	return numInfantryCards + numCavalryCards + numArtilleryCards;;
}

int Player::getNumInfantryCards() const
{
	return numInfantryCards;
}

int Player::getNumCavalryCards() const
{
	return numCavalryCards;
}

int Player::getNumArtilleryCards() const
{
	return numArtilleryCards;
}

bool Player::hasThreeDifferent() const
{
	return numInfantryCards > 0 && numCavalryCards > 0 && numArtilleryCards > 0;
}

bool Player::hasTreeSame() const
{
	return numInfantryCards > 2 || numCavalryCards > 2 || numArtilleryCards > 2;
}

void Player::removeThreeDifferent()
{
	numInfantryCards--;
	numCavalryCards--;
	numArtilleryCards--;
}

void Player::removeThreeSame(int index)
{
	switch (index)
	{
	case 0:
		numInfantryCards -= 3;
		break;
	case 1:
		numCavalryCards -= 3;
		break;
	case 2:
		numArtilleryCards -= 3;
		break;
	default:
		break;
	}
}
