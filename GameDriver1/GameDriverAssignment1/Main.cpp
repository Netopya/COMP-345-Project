#include <iostream>
#include <string>

/*
Michael Bilinsky 26992358
COMP 345 Assignment #1 - Part 2: Game driver

The shell of a game driver for a Risk game.
Only plays through two turns of the game and
displays to the players what phase of their
turn it is.

*/

using namespace std;

const int NUM_PLAYERS = 4;
const int NUM_PHASES = 3;
const string PHASES[] = {"Reinforcement", "Attack", "Fortification"};
int runGame();

int main()
{
	int exitCode = 0;

	cout << "Welcome to the Risk game driver" << endl;

	exitCode = runGame();

	cout << endl << "The game has stopped running" << endl;
	system("pause");
	return exitCode;
}

int runGame()
{
	bool gameOver = false;
	int turnNumber = 0;

	// Loop until the game has ended
	while (!gameOver)
	{
		turnNumber++;

		cout << "ROUND " << turnNumber << endl;

		// Loop through the players
		for (int i = 0; i < NUM_PLAYERS; i++)
		{
			// Loop through the phases of the game
			for (int j = 0; j < NUM_PHASES; j++)
			{
				cout << "Player " << i + 1 << " perform your " << PHASES[j] << " move" << endl;
				system("pause");

			}
		}

		// In this "demo" only play two rounds
		gameOver = turnNumber > 1;
	}

	return 0;
}