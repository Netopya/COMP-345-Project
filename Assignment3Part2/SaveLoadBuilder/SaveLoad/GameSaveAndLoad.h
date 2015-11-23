#pragma once

class GameSaveAndLoad // Director
{
private:
	class SaveLoadBuilder* saveLoadBuilder;
public:
	void setSaveLoadBuilder(class SaveLoadBuilder* saveLoadBuilder);
	void ConstructSaveLoadOperation();
};
