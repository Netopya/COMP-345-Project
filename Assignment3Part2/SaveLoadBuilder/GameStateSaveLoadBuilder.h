#pragma once

#include "SaveLoadBuilder.h"

class GameStateSaveLoadBuilder : public SaveLoadBuilder
{
private:
	Player* playerTurn;
	string phase;
	const string ID = "GAMEINFO";
public:
	GameStateSaveLoadBuilder(class Player* playerTurn, string phase);
	void writeElements(ofstream file) override;
};