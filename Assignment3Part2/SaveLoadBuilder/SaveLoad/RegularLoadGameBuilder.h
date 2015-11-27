#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include "SaveLoadBuilder.h"

using namespace std;

/*
A builder that constructs a saveinstance based off of a saved game file
*/

class RegularLoadGameBuilder : public SaveLoadBuilder
{
private:
	ifstream file;
public:

	virtual void initializeSaveLoad() override;
	virtual void buildPlayers() override;
	virtual void buildGameState() override;
	virtual void buildWorld() override;
	virtual void endSaveLoad() override;
};