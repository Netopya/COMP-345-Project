#pragma once

#include <iostream>
#include <fstream>
using namespace std;

class SaveLoadBuilder
{
protected:
	const string PLAYERID = "PLAYERINFO";
	const string WORLDID = "WORLDINFO";
	const string GAMEID = "GAMEINFO";
public:
	virtual void initializeSaveLoad() = 0;
	virtual void buildPlayers() = 0;
	virtual void buildGameState() = 0;
	virtual void buildWorld() = 0;
	virtual void endSaveLoad() = 0;
};