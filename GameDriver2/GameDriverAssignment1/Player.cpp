#include <iostream>
#include "Player.h"

using namespace std;

Player::Player(string playerName)
{
	this->playerName = playerName;
	alive = true;
}

string Player::GetPlayerName()
{
	return playerName;
}

const vector<Country*> Player::GetCountries()
{
	return countries;
}

void Player::AddCountry(Country *country)
{
	countries.push_back(country);
}

void Player::Attack()
{
	if (alive)
	{
		// Randomly find a country to destroy
		int randomCountry = countries.size() > 1 ? rand() % (countries.size() - 1) : 0;
		Country* destroyedCountry = countries[randomCountry];

		// Remove the country from assigned countries
		countries.erase(countries.begin() + randomCountry);

		cout << "The country of " << destroyedCountry->GetCountryName() << " was destroyed!" << endl;

		// Delete the country, don't need it anymore in the game
		delete destroyedCountry;

		// "Kill" the player if they don't have anymore countries
		if (countries.size() == 0)
		{
			alive = false;
			cout << "All of " << GetPlayerName() << "'s countries have been destoyed" << endl << GetPlayerName() << " has been eliminated!" << endl;
		}
	}
}

const bool Player::Alive()
{
	return alive;
}
