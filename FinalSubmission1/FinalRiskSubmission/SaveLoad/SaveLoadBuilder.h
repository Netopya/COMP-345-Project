#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "GameSaveInstance.h"

using namespace std;

class SaveLoadBuilder
{
protected:
	GameSaveInstance* saveInstance;

	// ID's to identify headers in the game save file
	const string PLAYERID = "PLAYERINFO";
	const string WORLDID = "WORLDINFO";
	const string GAMEID = "GAMEINFO";
	const char SPACECHAR = '~';

	// Since spaces are a delimiting character, replace them by a ~
	string encodeString(string unencoded) { 
		replace(unencoded.begin(), unencoded.end(), ' ', SPACECHAR); 
		return unencoded;
	}

	string decodeString(string encoded)
	{
		replace(encoded.begin(), encoded.end(), SPACECHAR, ' ');
		return encoded;
	}
public:
	virtual void initializeSaveLoad() = 0;
	virtual void buildPlayers() = 0;
	virtual void buildGameState() = 0;
	virtual void buildWorld() = 0;
	virtual void endSaveLoad() = 0;

	GameSaveInstance* getSave() { return saveInstance; }
};