#ifndef GAMELOGDECORATOR_H
#define GAMELOGDECORATOR_H

#include <string>
#include <iostream>
#include <vector>
#include "..\GameLog\GameLog.h"
#include "..\GameLog\SimpleGameLog.h"

using namespace std;


class GameLogDecorator : public GameLog 
{
protected:
	GameLog* decoratedGameLog;
public:

	GameLogDecorator() {
		this->decoratedGameLog = new SimpleGameLog();
	}

	GameLogDecorator(GameLog *decoratedGameLog) {
		this->decoratedGameLog = decoratedGameLog;
	}

	void LogAction(string player, int phase, string str) {
		decoratedGameLog->LogAction(player, phase, str);
	}
	void printLastAction() {
		decoratedGameLog->printLastAction();
	}
	bool okToPrint(string player, int phase) {
		return decoratedGameLog->okToPrint(player, phase);
	}

};
#endif