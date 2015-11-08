#pragma once

#include <string>
#include <vector>
using namespace std;

class Player {

private:
	string playerName;

public:
	Player(string);
	string GetPlayerName();
};