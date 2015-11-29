#include "GameSaveAndLoad.h"
#include "SaveLoadBuilder.h"
#include "GameSaveInstance.h"

void GameSaveAndLoad::setSaveLoadBuilder(SaveLoadBuilder* saveLoadBuilder)
{
	this->saveLoadBuilder = saveLoadBuilder; // Set the concrete builder
}

void GameSaveAndLoad::ConstructSaveLoadOperation()
{
	saveLoadBuilder->initializeSaveLoad();
	saveLoadBuilder->buildPlayers();
	saveLoadBuilder->buildGameState();
	saveLoadBuilder->buildWorld();
	saveLoadBuilder->endSaveLoad();
}

GameSaveInstance* GameSaveAndLoad::getSave()
{
	return saveLoadBuilder->getSave(); // Get the constructed save/load instance
}
