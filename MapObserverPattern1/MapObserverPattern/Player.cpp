#include <iostream>
#include "Player.h"

using namespace std;

Player::Player(string playerName)
{
	this->playerName = playerName;
}

string Player::GetPlayerName()
{
	return playerName;
}
