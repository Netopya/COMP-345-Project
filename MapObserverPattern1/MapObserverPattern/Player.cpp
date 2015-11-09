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

string Player::GetPlayerName(int max)
{
	string foo = playerName.substr(0, max);
	return foo;
}

const bool Player::isAlive()
{
	return alive;
}

void Player::kill()
{
	alive = false;
}
