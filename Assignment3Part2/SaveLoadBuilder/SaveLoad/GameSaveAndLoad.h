#pragma once

/*
This class is the director for the save/load builder pattern
*/

class GameSaveAndLoad // Director
{
private:
	class SaveLoadBuilder* saveLoadBuilder;
public:
	void setSaveLoadBuilder(class SaveLoadBuilder* saveLoadBuilder);
	void ConstructSaveLoadOperation();
	class GameSaveInstance* getSave();
};
