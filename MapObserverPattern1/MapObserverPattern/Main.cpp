#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <algorithm>
#include "Player.h"
#include "Country.h"
#include "Map.h"
#include "MapView.h"

/*
Michael Bilinsky 26992358
COMP 345 Assignment #1 - Part 2: Game driver

The shell of a game driver for a Risk game.
The program asks for a number of players and their names.
The game has a fixed number of countries.
Battling and other phases of the game are not yet eliminated.
Players will win every battle and will randomly destoy one of their enemy's countries.
Ownership of countries are not transfered, instead countries are permenatly removed for this demo.
Last player with countries remaining wins.
*/

using namespace std;

int numberPlayers; // Number of players
vector<Player*> players; // List of players
const int NUM_PHASES = 3;
const string PHASES[] = { "Reinforcement", "Attack", "Fortification" };
const int NUM_COUNTRIES = 10;

// Temporary manually entered list of countries
const string MAP_INPUT[][3] = 
{ { "Canada", "USA", "Foolandia" },
{ "Foolandia", "Canada","Iceland" },
{ "USA", "Canada", "Mexico" },
{ "UK", "Ukraine", "Iceland" },
{ "Mexico", "USA", "Egypt" },
{ "Ukraine", "UK", "China" },
{ "China", "Ukraine", "Australia" },
{ "Australia", "Egypt", "China" },
{ "Egypt", "Mexico", "Australia" },
{ "Iceland", "Foolandia", "UK" } };

const string CONTINENTS[] = { "N. America", "N. America", "N. America", "Europe", "N. America", "Europe","Asia","Oceania", "Africa", "Europe" };

Map map;
MapView* mapView;

// Ask for number of players and their names
void queryPlayers();

// Assign countries to players
void assignCountries();

// Print out the players and the countries they hold
//void printCountries();

// Run the game
void runGame();

// Allow the player to perform their reinforcement move
void playerReinforce(Player*);

// Allow the player to perform their attack move
void playerAttack(Player*);

// Allow the player to perform their fortification move
void playerFortify(Player*);

void checkPlayerAndKill(Player*);

int main()
{
	mapView = new MapView(&map);

	cout << "Welcome to the Risk game driver" << endl;

	// Randomize the random number generator using the current time as a seed
	srand(time(NULL));

	queryPlayers();

	assignCountries();

	map.notifyObservers();

	runGame();

	cout << endl << "The game has stopped running" << endl;
	system("pause");
	return 0;
}

void queryPlayers()
{
	bool numEntered = false;

	// Loop until a valid input is provided
	while (!numEntered)
	{
		cout << "Please enter the number of players" << endl;
		cin >> numberPlayers;

		if (numberPlayers > 1 && numberPlayers <= NUM_COUNTRIES)
		{
			numEntered = true;
		}
		else
		{
			cout << "Please specify between 2 and " << NUM_COUNTRIES << " players" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
		}
	}

	cin.ignore();

	// Ask for the player names and use the name to create a new player
	for (int i = 0; i < numberPlayers; i++)
	{
		cout << "Enter the name of player " << i + 1 << endl;
		string playerName;
		getline(cin, playerName);
		Player* newPlayer = new Player(playerName);
		players.push_back(newPlayer);
	}
}

void assignCountries()
{
	
	for (int i = 0; i < NUM_COUNTRIES; i++)
	{
		// Create the countries
		map.addCountry(new Country(MAP_INPUT[i][0], CONTINENTS[i]));
	}

	vector<Country*> newCountries(map.GetCountries());

	for (int i = 0; i < NUM_COUNTRIES; i++)
	{
		for (int j = 1; j < 3; j++)
		{
			newCountries[i]->addAdjecentCountry(map.getCountryByName(MAP_INPUT[i][j]));
		}
	}


	// Number of countries that can be evenly distributed
	int numFairCountries = (NUM_COUNTRIES / numberPlayers) * numberPlayers;

	// Number of extra countries
	int numExtraCountries = NUM_COUNTRIES % numberPlayers;

	

	// Randomly and evenly assign countries to players
	for (int i = 0; i < numFairCountries; i++)
	{
		// Select a random country
		int randomCountry = newCountries.size() > 1 ? rand() % (newCountries.size() - 1) : 0;
		Country* selectedCountry = newCountries[randomCountry];

		// Remove the country from available countries
		newCountries.erase(newCountries.begin() + randomCountry);

		// Assign the country to the player
		//players[i % numberPlayers]->AddCountry(selectedCountry);
		selectedCountry->setControllingPlayer(players[i % numberPlayers]);
	}

	// If there are no extra countries, return
	if (!(numExtraCountries > 0))
	{
		return;
	}

	vector<Player*> luckPlayers(players);

	// Find players who will be lucky enough to receive an extra country
	for (int i = 0; i < numberPlayers - numExtraCountries; i++)
	{
		// Randomly select a player and remove them from potential candidacy for extra countries
		int randomPlayer = rand() % (luckPlayers.size() - 1);
		luckPlayers.erase(luckPlayers.begin() + randomPlayer);
	}

	// Assign the remaining countries to the remaining lucky players
	for (unsigned i = 0; i < luckPlayers.size(); i++)
	{
		//luckPlayers[i]->AddCountry(newCountries[i]);
		newCountries[i]->setControllingPlayer(luckPlayers[i]);
	}
}

/*
void printCountries()
{
	// Print the players and the countries they hold
	for (unsigned i = 0; i < players.size(); i++)
	{
		vector<Country*> playerCountries(players[i]->GetCountries());

		cout << players[i]->GetPlayerName() << " current holds: " << endl;

		for (unsigned j = 0; j < playerCountries.size(); j++)
		{
			cout << "     " << playerCountries[j]->GetCountryName() << endl;
		}
	}
}*/

void runGame()
{
	bool gameOver = false;
	int turnNumber = 0;
	Player* winner = NULL;

	// Loop until the game has ended
	while (!gameOver)
	{
		turnNumber++;

		cout << endl << "ROUND " << turnNumber << endl;

		//printCountries();

		// Loop through the players
		for (int i = 0; i < numberPlayers; i++)
		{
			// If the player is dead, skip their turn
			
			if (!players[i]->isAlive())
			{
				cout << endl << players[i]->GetPlayerName() << " is eliminated" << endl;
				system("pause");
				continue;
			}
			

			// Loop through the phases of the game
			for (int j = 0; j < NUM_PHASES; j++)
			{
				cout << endl << players[i]->GetPlayerName() << " perform your " << PHASES[j] << " move" << endl;

				switch (j)
				{
				case 0:
					playerReinforce(players[i]);
					break;
				case 1:
					playerAttack(players[i]);
					break;
				case 2:
					playerFortify(players[i]);
					break;
				}


				system("pause");

			}
		}

		// If there is only one player left, they are the winner
		int alivePlayers = 0;
		for (int i = 0; i < numberPlayers; i++)
		{
			
			if (players[i]->isAlive())
			{
				alivePlayers++;
				winner = players[i]; // This player is in fact the winner since they are the only one that will be alive
			}
		}

		gameOver = alivePlayers < 2;

	}

	// Annouce the winner
	if (winner)
	{
		cout << endl << "GAME OVER" << endl << "The winner is " << winner->GetPlayerName() << endl << "Thank you for playing" << endl;
	}
}

void playerReinforce(Player* player)
{
	cout << "Reinforcement phase not yet implemented" << endl;
}

void playerAttack(Player* player)
{
	bool validCountry = false;
	Country* playerCountry = NULL;
	Country* enemyCountry = NULL;
	while (!validCountry)
	{
		string inCountry;
		cout << "Ever a country to attack with: " << endl;
		cin >> inCountry;

		playerCountry = map.getCountryByName(inCountry);
		if (playerCountry)
		{
			if (playerCountry->getOwner() == player)
			{
				vector<Country*> adjacentCountries(playerCountry->getAdjacentCountries());

				for (unsigned i = 0; i < adjacentCountries.size(); i++)
				{
					if (adjacentCountries[i]->getOwner() != player)
					{
						validCountry = true;
						break;
					}

					if (i == adjacentCountries.size() - 1)
					{
						cout << "You cannot attack any enemies from that country" << endl;
					}
				}
			}
			else
			{
				cout << "You do not control that country" << endl;
			}
		}
		else
		{
			cout << "You did not enter a valid country" << endl;
		}
	}
	
	validCountry = false;

	while (!validCountry)
	{
		string inCountry;
		cout << "Ever a country to attack: " << endl;
		cin >> inCountry;

		enemyCountry = map.getCountryByName(inCountry);

		if (enemyCountry)
		{
			if (enemyCountry->getOwner() == player)
			{
				cout << "You cannot attack your own country" << endl;
				continue;
			}

			vector<Country*> adjacentCountries(playerCountry->getAdjacentCountries());

			for (unsigned i = 0; i < adjacentCountries.size(); i++)
			{
				if (adjacentCountries[i] == enemyCountry)
				{
					validCountry = true;
					break;
				}

				if (i == adjacentCountries.size() - 1)
				{
					cout << "You cannot attack that enemy from your country" << endl;
				}
			}
		}
		else
		{
			cout << "You did not enter a valid country" << endl;
		}
	}

	Player* enemy = enemyCountry->getOwner();
	
	int attackingArmies = playerCountry->getNumArmies();
	int defendingArmies = enemyCountry->getNumArmies();

	if (attackingArmies > defendingArmies)
	{
		enemyCountry->setControllingPlayer(player);
		map.notifyObservers();
		cout << "You took over the country!" << endl;
	}
	else
	{
		playerCountry->setControllingPlayer(enemyCountry->getOwner());
		map.notifyObservers();
		cout << "You lost the battle and the enemy has taken over the country!" << endl;
	}

	checkPlayerAndKill(player);
	checkPlayerAndKill(enemy);
}

void checkPlayerAndKill(Player* player)
{
	vector<Country*> countries(map.GetCountries());
	for (unsigned i = 0; i < countries.size(); i++)
	{
		if (countries[i]->getOwner() == player)
		{
			return;
		}
	}

	player->kill();
	cout << player->GetPlayerName() << " has lost all of their countries" << endl;

}

void playerFortify(Player* player)
{
	cout << "Fortification phase not yet implemented" << endl;
}