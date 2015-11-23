#include "GameStateSaveLoadBuilder.h"

GameStateSaveLoadBuilder::GameStateSaveLoadBuilder(Player* playerTurn, string phase)
{
	this->playerTurn = playerTurn;
	this->phase = phase;
}

void GameStateSaveLoadBuilder::writeElements(ofstream file)
{
	file << ID.c_str() << ' ' << playerTurn->GetPlayerName() << ' ' << phase << endl;
}