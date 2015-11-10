#pragma once

/*
Michael Bilinsky 26992358
COMP 345 Assignment #2 - Part 2: Map Observer Pattern

Player in the game, they have a name and an alive status
*/

#include <string>
#include <vector>
using namespace std;

class Player {

private:
	string playerName;
	bool alive;
public:
	Player(string);
	string GetPlayerName();
	string GetPlayerName(int); // Get the player's name truncated to a max length
	const bool isAlive();
	void kill();
};