#include "PlayerSaveLoadBuilder.h"
#include "Player\Player.h"

PlayerSaveLoadBuilder::PlayerSaveLoadBuilder(vector<Player*>* players)
{
	this->players = players;
}

void PlayerSaveLoadBuilder::writeElements(ofstream file)
{
	file << ID.c_str() << ' ' << players->size() << endl;

	for (unsigned i = 0; i < players->size(); i++)
	{
		file << players->at(i)->GetPlayerName() << ' ' << endl;
	}
}