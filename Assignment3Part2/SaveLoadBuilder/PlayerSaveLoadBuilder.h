#pragma once

#include <vector>
#include "SaveLoadBuilder.h"

class PlayerSaveLoadBuilder : public SaveLoadBuilder
{
private:
	class vector<class Player*>* players;
	const string ID = "PLAYERINFO";
public:
	PlayerSaveLoadBuilder(vector<class Player*>* players);
	void writeElements(ofstream file) override;
};
