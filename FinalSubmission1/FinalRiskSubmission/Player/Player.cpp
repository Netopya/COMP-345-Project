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


void Player::setStrat(Strategy* type)
{
	if (strat != nullptr) {
		delete strat;
	}
	strat = type;
}
string Player::executeStrategy()
{
	return this->strat->executeSource(this->getCountries());
}
string Player::executeStrategyTarget(Country*  selectCountry)
{
	return this->strat->executeTarget(selectCountry);
}
void Player::gainCard() {
	int rnd = rand() % 3;
	switch (rnd) {
	case 0:
		soldier++;
		cout << "Gained a Soldier Card." << endl;
		break;
	case 1:
		cavalry++;
		cout << "Gained a Soldier Card." << endl;
		break;
	case 2:
		artillery++;
		cout << "Gained a Soldier Card." << endl;
		break;
	}
}
void Player::gainCard(int i) {
	int rnd =  i;
	switch (rnd) {
	case 0:
		soldier++;
		break;
	case 1:
		cavalry++;
		break;
	case 2:
		artillery++;
		break;
	}
}
int Player::checkCardsBonus() {
	int bonus = 0;
	while (soldier > 3) {
		soldier -= 3;
		cardBonus += 1;
		bonus += cardBonus * 5;
		cout << "Cardbonus increased" << endl;
	}
	while (cavalry > 3) {
		cavalry -= 3;
		cardBonus += 1;
		bonus += cardBonus * 5;
		cout << "Cardbonus increased" << endl;
	}
	while (artillery > 3) {
		artillery -= 3;
		cardBonus += 1;
		bonus += cardBonus * 5;
		cout << "Cardbonus increased" << endl;
	}
	while (soldier > 0 && cavalry > 0 && artillery > 0) {
		soldier--;
		cavalry--;
		artillery--;
		cardBonus += 1;
		bonus += cardBonus * 5;
		cout << "Cardbonus increased" << endl;
	}
	return bonus;
}

void Player::giveCards(Player* other) {
	cout << other->GetPlayerName() << " has taken cards from " << this->GetPlayerName() << endl;
	while (soldier > 0) {
		other->gainCard(0);
		soldier--;
	}

	while (cavalry > 0) {
		other->gainCard(1);
		cavalry--;
	}

	while (artillery > 0) {
		other->gainCard(2);
		artillery--;
	}
}