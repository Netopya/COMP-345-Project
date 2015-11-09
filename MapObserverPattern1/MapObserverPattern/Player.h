#pragma once

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
	string GetPlayerName(int);
	const bool isAlive();
	void kill();
};