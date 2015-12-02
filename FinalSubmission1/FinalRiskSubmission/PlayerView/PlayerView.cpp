#include "PlayerView.h"

PlayerView::PlayerView(MyObservable* const& observable)
{
	observable->addObserver((MyObserver*)this);
}

void PlayerView::update(MyObservable* observable)
{
	Player* player = (Player*)observable;

	if (player)
	{
		//Display player information.
		cout << "Player name: " << player->GetPlayerName() << endl;
		cout << "Number of armies: " << player->getNumArmies() << endl;
		cout << "Number of battles one: " << player->getNumWins() << endl;
		cout << "Cards: " << player->getNumInfantryCards() << " Infantry, " << player->getNumCavalryCards() << " Cavalry, " << player->getNumArtilleryCards() << " Artillery" << endl;
		cout << "Countries controlled: " << endl;

		vector<Country*> countries = player->getCountries();

		for (unsigned i = 0; i < countries.size(); i++)
		{
			cout << "\t" << countries[i]->getName() << endl;
		}

		cout << "Continents controlled: " << endl;

		vector<Continent*> continents = player->getContinents();

		for (unsigned i = 0; i < continents.size(); i++)
		{
			cout << "\t" << continents[i]->getName() << endl;
		}
	}
}