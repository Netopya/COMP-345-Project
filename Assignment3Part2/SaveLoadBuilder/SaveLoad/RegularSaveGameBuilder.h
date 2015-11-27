#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include "SaveLoadBuilder.h"

using namespace std;

/*
This builder save the current state of the game to a file
*/

class RegularSaveGameBuilder : public SaveLoadBuilder
{
private:
	ofstream file;
	class World* map;
	vector<class Player*>* players;
	class Player* playerTurn;
	string phase;
public:
	RegularSaveGameBuilder(class World* map, vector<class Player*>* players, class Player* playerTurn, string phase);

	virtual void initializeSaveLoad() override;
	virtual void buildPlayers() override;
	virtual void buildGameState() override;
	virtual void buildWorld() override;
	virtual void endSaveLoad() override;
};