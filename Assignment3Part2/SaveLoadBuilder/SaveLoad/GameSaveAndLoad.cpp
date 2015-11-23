#include "GameSaveAndLoad.h"
#include "SaveLoadBuilder.h"

void GameSaveAndLoad::setSaveLoadBuilder(SaveLoadBuilder* saveLoadBuilder)
{
	this->saveLoadBuilder = saveLoadBuilder;
}

void GameSaveAndLoad::ConstructSaveLoadOperation()
{
	saveLoadBuilder->initializeSaveLoad();
	saveLoadBuilder->buildPlayers();
	saveLoadBuilder->buildGameState();
	saveLoadBuilder->buildWorld();
	saveLoadBuilder->endSaveLoad();

	//TODO: return a contrusted object
}