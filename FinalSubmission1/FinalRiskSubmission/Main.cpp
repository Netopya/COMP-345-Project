#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <algorithm>
#include "World\World.h"
#include "MapView\MapView.h"
#include "PlayerView\PlayerView.h"

#include "GameLog\GameLog.h"
#include "GameLog\SimpleGameLog.h"
#include "GameLog\PlayerGameLog.h"
#include "GameLog\PhaseGameLog.h"
#include "GameLogView\GameLogView.h"

#include "SaveLoad\RegularSaveGameBuilder.h"
#include "SaveLoad\RegularLoadGameBuilder.h"
#include "SaveLoad\GameSaveAndLoad.h"


using namespace std;

/*
Michael Bilinsky 26992358
Mina Abdel Malek 26951791
Maxime Morin 27501455
Pawel-Stanislaw Obiedzinski 22026643

COMP 345 Project Intermediate Build

-A game of classic risk
-Can load map from a file
-Can add countries and continents from a map editor
-Can save new maps
-Can play through the reinforement, attack, and fortification phases of the game
-Attacking is in a simplified form (no dice implemented)
-Cards are not yet implemented

See README.txt for Visual Studio compilation information
*/

int numberPlayers; // Number of players
int numberComputerPlayers; // Number of AI players
vector<Player*> players; // List of players
const int NUM_PHASES = 3;
const string PHASES[] = { "Reinforcement", "Attack", "Fortification" };
int num_Countries;
int gameSavingMode = 1;

World* map;
MapView* mapView; // The map view component


GameLog* gameLog;
GameLogView* gameLogView;
void settingGameLog();


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

void mapEditor();	// Run the map editor
void addCountry();	// Add a country
void addContinent();// Add a continent
void addLink();		// Add links between countries
void saveMap();		// Save the map to a file

string queryMapFile(); //Ask for the map file to load

// Request an integer from the user, showing an error message until they enter a valid number within the bounds
int requestInt(string question, string errorMessage, int min, int max);

void saveGame(int player, int phase); // Save the game
bool restorePhaseFromSave = false;
int phaseToRestore = -1;
int playerToRestore = -1;


int main()
{
	cout << "Welcome to RISK!" << endl;

	int mapOption = requestInt("Would you like to: \n 1. Load map \n 2. Create new map", "You did not enter 1 or 2", 1, 2);

	// If creating a new map, go directly into the map editor
	if (mapOption == 2)
	{
		map = new World();

		// Setup the map view
		mapView = new MapView(map);

		mapEditor();

		mapView->setEditorMode(false);
	}
	else
	{
		// Setup the map
		map = new World(queryMapFile().c_str());
		// Setup the map view
		mapView = new MapView(map);
	}

	// Check if the map was correctly loaded/created
	if (!(map->getCountries()->size() > 0))
	{
		cout << "Could not load map file" << endl;
		cout << "Error: " << map->getLastErrorMessage() << endl;
		cout << "Goodbye!" << endl;
		system("pause");
		return 1;
	}



	bool inMainMenu = true;

	while (inMainMenu)
	{
		system("cls");

		// Ask for the game mode
		int gameMode = requestInt("What would you like to do today? \n 1. Play Game \n 2. Edit Map \n 3. Load Saved Game \n 4. Configure Game Saving Settings", "Please enter a selection of 1, 2, 3 or 4", 1, 4);


		if (gameMode == 2)
		{
			inMainMenu = false;
			mapEditor();
		}
		else if (gameMode == 3)
		{
			// load a saved game
			SaveLoadBuilder* loadBuilder = new RegularLoadGameBuilder();
			GameSaveAndLoad save;
			save.setSaveLoadBuilder(loadBuilder);
			save.ConstructSaveLoadOperation();
			GameSaveInstance* instance = save.getSave();
			players = *(instance->createPlayers(map));
			instance->addArmiesAndPlayersToMap(map);

			numberPlayers = players.size();


			// Setup restoring to the saved phase
			restorePhaseFromSave = true;


			for (int i = 0; i < NUM_PHASES; i++)
			{
				if (instance->getPhase() == PHASES[i])
				{
					phaseToRestore = i;
				}
			}

			for (int i = 0; i < numberPlayers; i++)
			{
				// Check if any players are already dead
				checkPlayerAndKill(players[i]);

				if (instance->getPlayer() == players[i]->GetPlayerName())
				{
					playerToRestore = i;
				}
			}

			if (phaseToRestore < 0 || playerToRestore < 0)
			{
				instance->setError(true, "Invalid phase or player in game save");
			}

			delete loadBuilder;

			// Setup the number of countries
			num_Countries = (int)map->getCountries()->size();


			inMainMenu = false;

			if (instance->errorOccured())
			{
				cout << "Could not load game save. The following error occured: " << instance->getLastError() << endl;
				system("pause");
			}
			else
			{
				settingGameLog();// Dependent on Player List must be after players = *(instance->createPlayers(map));

				// All is well, proceed into the game
				runGame();
			}
		}
		else if (gameMode == 4)
		{
			// Give the user the option of configuring how saving the game will be handled

			int option = requestInt("How would you like to configure game saving? Currently selected: " + to_string(gameSavingMode) + "\n 1. Ask for save \n 2. Automatically save \n 3. Never save \n 4. Return to previous menu", "You did not enter a valid number", 1, 4);
			if (option > 0 && option < 4)
			{
				gameSavingMode = option;
				cout << "Game save option updated" << endl;
				system("pause");
			}
		}
		else
		{
			// else run the normal game

			cout << "Welcome to the Risk game" << endl;

			// Setup the number of countries
			num_Countries = (int)map->getCountries()->size();

			queryPlayers();

			settingGameLog();// Dependent on Player List must be after queryPlayers();

			assignCountries();

			map->notifyObservers();

			inMainMenu = false;

			runGame();
		}
	}

	cout << endl << "The game has stopped running" << endl;
	system("pause");
	return 0;
}

string queryMapFile()
{
	// ask for a file name
	string filename;
	cout << "Enter the name of the map file to load" << endl;
	cin >> filename;
	return "MapRessourceFiles\\" + filename;
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
		cout << "4. Save changes" << endl;
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
	// Ask for a country and the continent to put it on

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
	// Ask for the name of a new continent

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
	// Ask for the inital country from which the links will stem
	string countryName;
	cout << "Which country would you like to add links to?" << endl;
	getline(cin, countryName);

	bool validInput = false;
	int numLinks = 0;

	// Loop until a valid input is received for the number of links to add
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

	// Ask for the name of the country for each of the links
	for (int i = 0; i < numLinks; i++)
	{
		cout << "Enter the name of linked country #" << (i + 1) << endl;
		string* inputCountry = new string();
		getline(cin, *inputCountry);
		placesToLink->push_back(inputCountry->c_str());
	}

	// Add the links in the map
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

	// Make sure that all the countries have at least one link to another country
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
		// Ask for a file name
		string filename;
		cout << "Enter the name of the new file" << endl;
		cin >> filename;
		filename += ".map";

		// Save the file
		map->toFile(filename.c_str());
	}
}

void queryPlayers()
{
	bool numEntered = false;

	numberPlayers = requestInt("Please enter the number of players", "Please specify between 2 and " + to_string(num_Countries) + " players", 2, num_Countries);

	numberComputerPlayers = requestInt("Please enter the number of computer players", "Please specify between 0 and " + to_string(numberPlayers), 0, numberPlayers);

	// Ask for the player names and use the name to create a new player
	for (int i = 0; i < numberPlayers; i++)
	{
		bool computerPlayer = (numberPlayers - i) <= numberComputerPlayers;
		if (computerPlayer)
		{
			cout << "Enter the name of computer player " << i + 1 - (numberPlayers - numberComputerPlayers) << endl;
		}
		else
		{
			cout << "Enter the name of human player " << i + 1 << endl;
		}

		string playerName;
		getline(cin, playerName);
		Player* newPlayer = new Player(playerName, map, computerPlayer);
		PlayerView* playerview = new PlayerView(newPlayer);
		players.push_back(newPlayer);
	}
}

void assignCountries()
{
	vector<Country*> newCountries = *(map->getCountries());

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
			// Restore the player's turn from saved game
			if (restorePhaseFromSave)
			{
				i = playerToRestore;
			}

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
				// Display the updated map and player info
				map->notifyObservers();
				players[i]->notifyObservers();

				// If loading from save, restore the phase
				if (restorePhaseFromSave)
				{
					restorePhaseFromSave = false;
					j = phaseToRestore;
				}
				else
				{
					int option;

					switch (gameSavingMode)
					{
					case 1:
						// Ask for save
						option = requestInt("Would you like to save the game? \n 1. Yes \n 2. No", "You did not enter a valid option", 1, 2);
						if (option != 1)
						{
							break;
						}
					case 2:
						// Always save
						saveGame(i, j);
						break;
					case 3:
						// Never save
						break;
					default:
						break;
					}
				}

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
	vector<Country*> playerCountries = player->getCountries();

	// Get the number of reinforcements (atleast 1 army)
	int numReinforcements = max(1, (int)floor(playerCountries.size() / 3));

	// Loop until all the reinforcements are used up
	while (numReinforcements > 0)
	{
		if (player->isComputerPlayer())
		{
			// Random pick a country and add all armies to it
			int randomCountry = playerCountries.size() > 1 ? rand() % (playerCountries.size() - 1) : 0;
			playerCountries[randomCountry]->addArmies(numReinforcements);

			cout << "Computer player " << player->GetPlayerName() << " adds " << numReinforcements << " armies to " << playerCountries[randomCountry]->getName() << endl;

			numReinforcements = 0;
		}
		else
		{
			// Ask for a country to place armies on and ensure it is a valid choice
			cout << player->GetPlayerName() << ", you have " << numReinforcements << " reinforcement armies" << endl;
			cout << "Which country would you like to place some armies on?" << endl;

			string countryName;
			cin >> countryName;

			Country* country = map->getCountryFromName(countryName.c_str());
			if (country == NULL)
			{
				cout << "The country you entered does not exists" << endl;
				system("pause");
			}
			else if (country->getControllingPlayer() != player)
			{
				cout << "You do not countrol that country" << endl;
				system("pause");
			}
			else
			{
				bool validInput = false;
				int inputArmies = requestInt("How many armies would you like to place on " + string(country->getName()) + "?", "Please enter a number greater than 0 and less than or equal to " + numReinforcements, 1, numReinforcements);

				// Add the reinforcements to the country
				country->addArmies(inputArmies);

				// Remove the armies from available reinforcements
				numReinforcements -= inputArmies;




				//Game Log in Reinforcement phase
				string str = "Sent " + to_string(inputArmies) + " armies to " + countryName;
				gameLog->LogAction(player->GetPlayerName(), 0, str);
				if (gameLog->okToPrint(player->GetPlayerName(), 0)) {
					gameLog->notifyObservers();
				}
			}

		}

	}
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


	//Game Log in Attack phase
	string str = "Sent an Attack from" + string(playerCountry->getName()) + " onto target country: " + string(enemyCountry->getName());
	gameLog->LogAction(player->GetPlayerName(), 1, str);
	if (gameLog->okToPrint(player->GetPlayerName(), 1)) {
		gameLog->notifyObservers();
	}

	// Very simple attacking logic, if the attacker has more armies they win, else they lose
	if (attackingArmies > defendingArmies)
	{
		enemyCountry->setControllingPlayer(player);
		map->notifyObservers();
		cout << "You took over the country!" << endl;
		player->addWin();
	}
	else
	{
		playerCountry->setControllingPlayer(enemyCountry->getControllingPlayer());
		map->notifyObservers();
		cout << "You lost the battle and the enemy has taken over the country!" << endl;
		enemy->addWin();
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
	// Players need atleast 2 countries to fortify
	if (player->getCountries().size() < 2)
	{
		cout << "You do not have enough countries to fortify" << endl;
		system("pause");
	}

	int fortify;

	if (player->isComputerPlayer())
	{
		// Computer players never fortify
		cout << "Computer player " << player->GetPlayerName() << " decides not to fortify" << endl;
		fortify = 2;

	}
	else
	{
		fortify = requestInt("Would you like to fortify? \n 1. Yes \n 2. No", "Please enter 1 or 2", 1, 2);
	}


	if (fortify == 1)
	{
		bool validFortification = false;

		// Loop until the user has properly setup a fortification move
		while (!validFortification)
		{
			// Ask for the country to move units from
			cout << "Which country would you like to take units from?" << endl;
			string inputCountry;
			getline(cin, inputCountry);
			Country* country = map->getCountryFromName(inputCountry.c_str());

			if (country == NULL)
			{
				cout << "You did not enter a valid country" << endl;
			}
			else if (country->getControllingPlayer() != player)
			{
				cout << "You do not control that country" << endl;
			}
			else
			{
				bool canMove = false;

				// Quickly check if the user can even move out of the currently selected country
				for (unsigned i = 0; i < country->getConnectedCountries()->size(); i++)
				{
					if (country->getConnectedCountries()->at(i)->getControllingPlayer() == player)
					{
						canMove = true;
						break;
					}
				}

				if (!canMove)
				{
					cout << "You cannot move to an allied country from that country" << endl;
				}
				else
				{
					// Ask for the country to move units to
					cout << "Which country would you like to move units to?" << endl;

					string inputtoCountry;
					getline(cin, inputtoCountry);
					Country* toCountry = map->getCountryFromName(inputtoCountry.c_str());

					if (toCountry == NULL)
					{
						cout << "You did not enter a valid country" << endl;
					}
					else if (toCountry->getControllingPlayer() != player)
					{
						cout << "You do not control that country" << endl;
					}
					else if (!map->validPlayerPath(country, toCountry, player))
					{
						cout << "There is no path between the two countries" << endl;
					}
					else
					{
						int armyTransfer = requestInt("How many armies would you like to transfer?", "Please enter a number between 0 and " + country->getNumArmies(), 0, country->getNumArmies());

						// Remove the armies from the "from" country and move them to the "to" country
						country->removeArmies(armyTransfer);
						toCountry->addArmies(armyTransfer);

						validFortification = true;

						map->notifyObservers();


						//Game Log in Fortification phase
						string str = "Sent " + to_string(armyTransfer) + " armies from " + string(country->getName()) + "to country: " + string(toCountry->getName());
						gameLog->LogAction(player->GetPlayerName(), 2, str);
						if (gameLog->okToPrint(player->GetPlayerName(), 2)) {
							gameLog->notifyObservers();
						}
					}
				}

			}

		}
	}

}

int requestInt(string question, string errorMessage, int min, int max)
{
	bool validInput = false;
	int input;

	// Loop until a valid input is received
	while (!validInput)
	{
		// Ask user for input
		cout << question << endl;
		cin >> input;

		if (input >= min && input <= max)
		{
			validInput = true;
			cin.ignore();
		}
		else
		{
			// Show error message
			cout << errorMessage << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
		}
	}

	return input;
}

void settingGameLog()
{
	cout << "Game Log Configuraion" << endl;

	GameLog* gameLog2 = new SimpleGameLog;
	string playerRestrictQStr = "Restrict Game Log to a single player?\n0. No\n";
	for (int i = 0; i < players.size(); ++i)
	{
		playerRestrictQStr += to_string(i + 1) + ". " + players[i]->GetPlayerName() + "\n";
	}
	int playerRestrictQ = requestInt(playerRestrictQStr, "Invalid input, please enter the number corresponding to your selection.", 0, players.size());
	GameLog* gameLog1;
	if (playerRestrictQ == 0) {
		gameLog1 = gameLog2;
	}
	else {
		gameLog1 = new PlayerGameLog(players[playerRestrictQ - 1]->GetPlayerName(), gameLog2);
	}
	//GameLog* gameLog1 = new PlayerGameLog("p1", gameLog2);
	int phaseRestrictQ = requestInt("Restrict Game Log to a single phase?\n0. No\n1. Reinforcement\n2. Attack\n3. Fortification", "Invalid input, please enter the number corresponding to your selection.", 0, 3);
	switch (phaseRestrictQ) {
	case 0:
		gameLog = gameLog1;
		break;
	case 1:
		gameLog = new PhaseGameLog(0, gameLog1);
		break;
	case 2:
		gameLog = new PhaseGameLog(1, gameLog1);
		break;
	case 3:
		gameLog = new PhaseGameLog(2, gameLog1);
		break;
	}
	//	gameLog = new PhaseGameLog(0, gameLog1);
	GameLogView* gameLogView = new GameLogView(gameLog);
}

void saveGame(int player, int phase)
{
	// Save the game
	SaveLoadBuilder* saveBuilder = new RegularSaveGameBuilder(map, &players, players[player], PHASES[phase]);
	GameSaveAndLoad save;
	save.setSaveLoadBuilder(saveBuilder);
	save.ConstructSaveLoadOperation();
	delete saveBuilder;

}