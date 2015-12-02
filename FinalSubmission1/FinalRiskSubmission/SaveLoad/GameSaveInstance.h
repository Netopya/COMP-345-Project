#pragma once

#include <vector>

using namespace std;

// Struct to hold country info from the save file
struct CountryInfo
{
	string countryName;
	string owningPlayer;
	int numArmies;

	CountryInfo(string countryName, string owningPlayer, int numArmies)
	{
		this->countryName = countryName;
		this->owningPlayer = owningPlayer;
		this->numArmies = numArmies;
	}
};

struct PlayerInfo
{
	string playerName;
	bool isAI;

	PlayerInfo(string playerName, bool isAI)
	{
		this->playerName = playerName;
		this->isAI = isAI;
	}
};

/*
The class constructed by the save/load builder, holds an instance of the game
*/
class GameSaveInstance {

private: 
	vector<class Player*>* newPlayers;
	class Player* getPlayerByName(string playerName);
	bool hasError;
	string lastError;
public:
	GameSaveInstance();

	vector<PlayerInfo*> players;
	string playerTurn;
	string phase;
	vector<CountryInfo*> countryInfos;

	void addCountryInfo(string countryName, string owningPlayer, int numArmies);
	void addPlayerInfo(string playerName, bool isAI);

	void addArmiesAndPlayersToMap(class World* map);
	vector<class Player*>* createPlayers(class World* map);
	string getPhase();
	string getPlayer();

	void setError(bool error, string description);
	bool errorOccured();
	string getLastError();
};