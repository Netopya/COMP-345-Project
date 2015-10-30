#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "Player.h"
#include "Country.h"

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
const Country MAP[] = { {"Canada"}, {"Foolandia"}, {"USA"}, {"United Kingdom"}, {"Mexico"}, {"Ukraine"}, {"China"}, {"Australia"}, {"South Africa"}, {"Iceland"} };

// Ask for number of players and their names
void queryPlayers();

// Assign countries to players
void assignCountries();

// Print out the players and the countries they hold
void printCountries();

// Run the game
void runGame();

// Allow the player to perform their reinforcement move
void playerReinforce(Player*);

// Allow the player to perform their attack move
void playerAttack(Player*);

// Allow the player to perform their fortification move
void playerFortify(Player*);

int main()
{
	cout << "Welcome to the Risk game driver" << endl;

	// Randomize the random number generator using the current time as a seed
	srand(time(NULL));

	queryPlayers();

	assignCountries();

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
	// Number of countries that can be evenly distributed
	int numFairCountries = (NUM_COUNTRIES / numberPlayers) * numberPlayers;

	// Number of extra countries
	int numExtraCountries = NUM_COUNTRIES % numberPlayers;

	vector<Country*> newCountries;
	for (int i = 0; i < NUM_COUNTRIES; i++)
	{
		// Create the countries
		newCountries.push_back(new Country(MAP[i]));
	}

	// Randomly and evenly assign countries to players
	for (int i = 0; i < numFairCountries; i++)
	{
		// Select a random country
		int randomCountry = newCountries.size() > 1 ? rand() % (newCountries.size() - 1): 0;
		Country* selectedCountry = newCountries[randomCountry];

		// Remove the country from available countries
		newCountries.erase(newCountries.begin() + randomCountry);

		// Assign the country to the player
		players[i % numberPlayers]->AddCountry(selectedCountry);
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
		luckPlayers[i]->AddCountry(newCountries[i]);
	}
}

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
}

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

		printCountries();

		// Loop through the players
		for (int i = 0; i < numberPlayers; i++)
		{
			// If the player is dead, skip their turn
			if (!players[i]->Alive())
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
			if (players[i]->Alive())
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
	vector<Player*> enemies;
	for (unsigned i = 0; i < players.size(); i++)
	{
		// Enemies are alive and not the current player
		if (players[i]->Alive() && players[i] != player)
		{
			enemies.push_back(players[i]);
		}
	}

	cout << "Select the player to attack: " << endl;
	
	// Print out available players to attack
	for (unsigned i = 0; i < enemies.size(); i++)
	{
		cout << i + 1 << " - " << enemies[i]->GetPlayerName() << " : " << enemies[i]->GetCountries().size() << " countries" << endl;
	}

	bool numEntered = false;
	int selectedPlayer = 0;

	// Loop until a valid player id is provided
	while (!numEntered)
	{
		cin >> selectedPlayer;

		if (selectedPlayer > 0 && selectedPlayer <= (int)enemies.size())
		{
			numEntered = true;
		}
		else
		{
			cout << "Please specify a player ID between 1 and " << enemies.size() << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
		}
	}

	// Attack the selected player
	enemies[selectedPlayer - 1]->Attack();

}

void playerFortify(Player* player)
{
	cout << "Fortification phase not yet implemented" << endl;
}