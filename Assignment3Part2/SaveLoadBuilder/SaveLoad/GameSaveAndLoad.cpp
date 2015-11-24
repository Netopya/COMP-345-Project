#include "GameSaveAndLoad.h"
#include "SaveLoadBuilder.h"
#include "GameSaveInstance.h"

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

GameSaveInstance* GameSaveAndLoad::getSave()
{
	return saveLoadBuilder->getSave();
}
