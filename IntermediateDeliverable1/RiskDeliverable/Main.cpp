#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <algorithm>
#include "Player.h"
#include "Lib.h"
/*
Michael Bilinsky 26992358
COMP 345 Assignment #2 - Part 2: Map Observer Pattern

From Assignment #1:
-The gamedriver ask for players
-Countries are randomly assigned

New in Assignment #2
-Countries are placed in a map with an observer pattern
-The map is outputted in a nice table
-Countries are randomly assigned armies, RISK rules are not yet implemented
-attack/battle is not implement, instead a player will take over another country if they have more armies
-moving armies around is not implemented
*/

using namespace std;

int numberPlayers; // Number of players
vector<Player*> players; // List of players
const int NUM_PHASES = 3;
const string PHASES[] = { "Reinforcement", "Attack", "Fortification" };
int num_Countries;

// Temporary manually entered list of countries and their adjacencies, this will get read from a text file in the final version
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

// Mapping of the countries to continents, this will get read from a text file in the final version
const string CONTINENTS[] = { "N. America", "N. America", "N. America", "Europe", "N. America", "Europe","Asia","Oceania", "Africa", "Europe" };

World* map;
MapView* mapView; // The map view component

// Ask for number of players and their names
void queryPlayers();

// Assign countries to players
void assignCountries();

// Run the game
void runGame();

// Allow the player to perform their reinforcement move
void playerReinforce(Player*);

// Allow the player to perform their attack move
void playerAttack(Player*);

// Allow the player to perform their fortification move
void playerFortify(Player*);

// Check if a player has no countries and then kill them
void checkPlayerAndKill(Player*);

void mapEditor();
void addCountry();
void addContinent();
void addLink();
void saveMap();

string queryMapFile();

int main()
{
	cout << "Welcome to RISK!" << endl;

	// Setup the map
	map = new World(queryMapFile().c_str());

	if (!(map->getCountries()->size() > 0))
	{
		cout << "Could not load map file" << endl;
		cout << "Goodbye!" << endl;
		system("pause");
		return 1;
	}

	bool validInput = false;
	int gameMode = 0;
	while (!validInput)
	{
		cout << "What would you like to do today?" << endl;
		cout << "1. Play Game" << endl;
		cout << "2. Edit Map" << endl;
		cin >> gameMode;

		if (gameMode > 0 && gameMode < 3)
		{
			validInput = true;
			cin.ignore();
		}
		else
		{
			cout << "Please enter a selection of 1 or 2" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
			system("pause");
		}
	}


	mapView = new MapView(map);

	num_Countries = map->getCountries()->size();

	if (gameMode == 2)
	{
		mapEditor();
	}
	else
	{
		cout << "Welcome to the Risk game" << endl;

		// Randomize the random number generator using the current time as a seed
		srand(time(NULL));

		queryPlayers();

		assignCountries();

		map->notifyObservers();

		runGame();
	}
	cout << endl << "The game has stopped running" << endl;
	system("pause");
	return 0;
}

string queryMapFile()
{
	string filename;
	cout << "Enter the name of the map file to load" << endl;
	cin >> filename;
	return filename;
}

void mapEditor()
{
	bool editorRunning = true;
	mapView->setEditorMode(true);

	cout << "Welcome to the Risk Game map editor" << endl;

	while (editorRunning)
	{
		map->notifyObservers();

		cout << "What do you wish to do?" << endl;
		cout << "1. Add country" << endl;
		cout << "2. Add continent" << endl;
		cout << "3. Add link between countries" << endl;
		cout << "4. Save changes" << endl; // Check that link was added
		cout << "5. Exit" << endl;

		int choice;

		cin >> choice;

		if (choice > 0 && choice < 6)
		{
			cin.ignore();

			switch (choice)
			{
				case 1:
					addCountry();
					break;
				case 2:
					addContinent();
					break;
				case 3:
					addLink();
					break;
				case 4:
					saveMap();
					break;
				case 5:
					editorRunning = false;
					break;
			}
		}
		else
		{
			cout << "You did not enter a valid selection";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
			system("pause");
		}
	}
}

void addCountry()
{
	string* countryName = new string();
	string continentName;
	cout << "What is the name of the new country?" << endl;
	getline(cin, *countryName);

	cout << "On which continent is this country located?" << endl;
	getline(cin, continentName);

	

	bool success = map->addCountry(countryName->c_str(), continentName.c_str());

	if (!success)
	{
		cout << map->getLastErrorMessage() << endl;
		system("pause");
	}
}

void addContinent()
{
	string* continentName = new string();
	cout << "What is the name of the new continent?" << endl;
	getline(cin, *continentName);

	bool success = map->addContinent(continentName->c_str());
	if (!success)
	{
		cout << map->getLastErrorMessage() << endl;
		system("pause");
	}
}

void addLink()
{
	string countryName;
	cout << "Which country would you like to add links to?" << endl;
	getline(cin, countryName);

	bool validInput = false;
	int numLinks = 0;

	while (!validInput)
	{
		cout << "How many links would you like to add to " << countryName << endl;
		cin >> numLinks;

		if (numLinks > 0)
		{
			validInput = true;
		}
		else
		{
			cout << "Please enter a number greater than 0" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
		}
	}

	cin.ignore();

	vector<const char*>* placesToLink = new vector<const char*>();

	for (int i = 0; i < numLinks; i++)
	{
		cout << "Enter the name of linked country #" << (i + 1) << endl;
		string* inputCountry = new string();
		getline(cin, *inputCountry);
		placesToLink->push_back(inputCountry->c_str());
	}

	bool success = map->addLink(countryName.c_str(), placesToLink);

	if (!success)
	{
		cout << map->getLastErrorMessage();
		system("pause");
	}

	delete placesToLink;
}

void saveMap()
{
	bool mapValid = true;

	for (unsigned i = 0; i < map->getCountries()->size(); i++)
	{
		if (map->getCountries()->at(i)->getConnectedCountries()->size() < 1)
		{
			mapValid = false;
			break;
		}
	}

	if (!mapValid)
	{
		cout << "The map is not valid since a country is missing links" << endl;
		system("pause");
	}
	else
	{
		
		string filename;
		cout << "Enter the name of the new file" << endl;
		cin >> filename;
		filename += ".map";

		map->toFile(filename.c_str());
	}
}

void queryPlayers()
{
	bool numEntered = false;

	// Loop until a valid input is provided
	while (!numEntered)
	{
		cout << "Please enter the number of players" << endl;
		cin >> numberPlayers;

		if (numberPlayers > 1 && numberPlayers <= num_Countries)
		{
			numEntered = true;
		}
		else
		{
			cout << "Please specify between 2 and " << num_Countries << " players" << endl;
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
	
	//for (int i = 0; i < NUM_COUNTRIES; i++)
	{
		// Create the countries
		//map.addCountry(new Country(MAP_INPUT[i][0], CONTINENTS[i]));
	}

	vector<Country*> newCountries = *(map->getCountries());

	//for (int i = 0; i < NUM_COUNTRIES; i++)
	{
		for (int j = 1; j < 3; j++)
		{
			//newCountries[i]->addAdjecentCountry(map.getCountryByName(MAP_INPUT[i][j]));
		}
	}


	// Number of countries that can be evenly distributed
	int numFairCountries = (num_Countries / numberPlayers) * numberPlayers;

	// Number of extra countries
	int numExtraCountries = num_Countries % numberPlayers;

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

	// Ask the player for a country to attack with
	while (!validCountry)
	{
		string inCountry;
		cout << "Enter a country to attack with: " << endl;
		cin >> inCountry;

		playerCountry = map->getCountryFromName(inCountry.c_str()); //map.getCountryByName(inCountry);
		if (playerCountry)
		{
			// Check if the player controls that country
			if (playerCountry->getControllingPlayer() == player)
			{
				vector<Country*> adjacentCountries(*(playerCountry->getConnectedCountries()));

				// Make sure there are enemies in the adjacent countries
				for (unsigned i = 0; i < adjacentCountries.size(); i++)
				{
					if (adjacentCountries[i]->getControllingPlayer() != player)
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
			// Country could not be found
			cout << "You did not enter a valid country" << endl;
		}
	}
	
	validCountry = false;

	// Ask for a country to attack
	while (!validCountry)
	{
		string inCountry;
		cout << "Ever a country to attack: " << endl;
		cin >> inCountry;

		enemyCountry = map->getCountryFromName(inCountry.c_str());

		// Ensure the country is valid
		if (enemyCountry)
		{
			// Ensure the country is an enemy
			if (enemyCountry->getControllingPlayer() == player)
			{
				cout << "You cannot attack your own country" << endl;
				continue;
			}

			vector<Country*> adjacentCountries(*(playerCountry->getConnectedCountries()));

			// Make sure that the player can attack that country from the selected country
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

	Player* enemy = enemyCountry->getControllingPlayer();
	
	int attackingArmies = playerCountry->getNumArmies();
	int defendingArmies = enemyCountry->getNumArmies();

	// Very simple attacking logic, if the attacker has more armies they win, else they lose
	if (attackingArmies > defendingArmies)
	{
		enemyCountry->setControllingPlayer(player);
		map->notifyObservers();
		cout << "You took over the country!" << endl;
	}
	else
	{
		playerCountry->setControllingPlayer(enemyCountry->getControllingPlayer());
		map->notifyObservers();
		cout << "You lost the battle and the enemy has taken over the country!" << endl;
	}

	// Check if any of the players involved have been eliminated
	checkPlayerAndKill(player);
	checkPlayerAndKill(enemy);
}

void checkPlayerAndKill(Player* player)
{
	// If the player no longer controls any countries, then kill them

	vector<Country*> countries(*(map->getCountries()));
	for (unsigned i = 0; i < countries.size(); i++)
	{
		if (countries[i]->getControllingPlayer() == player)
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