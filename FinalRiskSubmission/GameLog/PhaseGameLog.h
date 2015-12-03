#ifndef PHASEGAMELOG_H
#define PHASEGAMELOG_H

#include <string>
#include <iostream>
#include <vector>
#include "..\GameLog\GameLogDecorator.h"

using namespace std;

/*
 * Phase restricted game log. Only allows game log to print when in correct phase, by overiding okToPrint method.
 */
class PhaseGameLog : public GameLogDecorator
{
protected:
	GameLog* decoratedGameLog;
public:
	int restrictedPhase;

	PhaseGameLog(int phase, GameLog *decoratedGameLog) {
		this->decoratedGameLog = decoratedGameLog;
		restrictedPhase = phase;
	}

	void LogAction(string player, int phase, string str) {
		decoratedGameLog->LogAction(player, phase, str);
	}
	void printLastAction() {
		decoratedGameLog->printLastAction();
	}
	bool okToPrint(string player, int phase) {
		return decoratedGameLog->okToPrint(player, phase) && (phase == restrictedPhase);
	}

};
#endif