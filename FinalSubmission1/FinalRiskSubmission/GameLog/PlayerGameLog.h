#ifndef PLAYERGAMELOG_H
#define PLAYERGAMELOG_H

#include <string>
#include <iostream>
#include <vector>
#include "..\GameLog\GameLogDecorator.h"

using namespace std;

/*
 * Plyaer restricted game log. Only allows game log to print when selected player is taking thier turn, by overiding okToPrint method.
 */
class PlayerGameLog : public GameLogDecorator
{
protected:
	GameLog* decoratedGameLog;
public:
	string restrictedPlayer;

	PlayerGameLog(string player,GameLog *decoratedGameLog) :GameLogDecorator(decoratedGameLog) {
		this->decoratedGameLog = decoratedGameLog;
		restrictedPlayer = player;
	}

	void LogAction(string player, int phase, string str) {
		decoratedGameLog->LogAction(player, phase, str);
	}
	void printLastAction() {
		decoratedGameLog->printLastAction();
	}
	bool okToPrint(string player, int phase) {
		return decoratedGameLog->okToPrint(player, phase) && (player == restrictedPlayer);
	}

};
#endif