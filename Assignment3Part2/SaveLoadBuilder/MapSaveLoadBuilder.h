#pragma once

#include "SaveLoadBuilder.h"

class MapSaveLoadBuilder : public SaveLoadBuilder
{
private:
	class World* map;
	const string ID = "WORLDINFO";
public:
	MapSaveLoadBuilder(class World* map);
	void writeElements(ofstream file) override;
};