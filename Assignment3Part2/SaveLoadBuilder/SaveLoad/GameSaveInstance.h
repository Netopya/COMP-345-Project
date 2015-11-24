#pragma once

#include <vector>

using namespace std;

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

class GameSaveInstance {

private: 
	vector<class Player*>* newPlayers;
	class Player* getPlayerByName(string playerName);
public:
	vector<string> players;
	string playerTurn;
	string phase;
	vector<CountryInfo*> countryInfos;

	void addCountryInfo(string countryName, string owningPlayer, int numArmies);
	
	void addArmiesAndPlayersToMap(class World* map);
	vector<class Player*>* createPlayers(class World* map);
};