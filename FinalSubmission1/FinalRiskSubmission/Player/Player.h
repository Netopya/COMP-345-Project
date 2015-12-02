#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <vector>
#include "..\MyObservable\MyObservable.h"
#include "..\World\World.h"

#include <ctime>
#include "..\Strategy\Strategy.h"
#include "..\Strategy\Deff.h"
#include "..\Strategy\Aggro.h"
#include "..\Strategy\RandomStrat.h"
class Strategy;

using namespace std;

/*
 * Player in the game, they have a name, an alive status,
 * and a number of wins along with methods to determine controlled armies,
 * countries, and continents.
 */
class Player : public MyObservable 
{
private:
	string playerName;
	bool alive;
	bool computerPlayer; //Is AI
	class World* map;
	int wins;
	Strategy *strat;
	int soldier=3, cavalry=3, artillery=3, cardBonus;
public:
	Player(string, World*, bool);
	string GetPlayerName();
	/*
	 * Get the player's name truncated to a max length.
	 */
	string GetPlayerName(int);
	bool isAlive();
	void kill();
	int getNumArmies();
	int getNumWins() const;
	void addWin();
	bool isComputerPlayer() const;
	/*
	 * Get controlled countries.
	 */
	vector<class Country*> getCountries();
	/*
	 * Get controlled continents.
	 */
	vector<class Continent*> getContinents();

	void setStrat(Strategy* type);
	string executeStrategy();
	string executeStrategyTarget(Country*  selectCountry);
	void gainCard();
	void gainCard(int i);
	int checkCardsBonus();


};
#endif