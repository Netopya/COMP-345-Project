#ifndef GAMELOG_H
#define GAMELOG_H

#include <string>
#include <iostream>
#include <vector>
#include "..\MyObservable\MyObservable.h"
#include "..\Player\Player.h"

using namespace std;

/*
 * Abstract class allowing a observer patern to be used with the game log and its decorator patern. To be used in conjunction with GameLogView class.
 */
class GameLog : public MyObservable 
{
public:

	virtual void LogAction(string player, int phase, string str) = 0;
	virtual void printLastAction() = 0;
	virtual bool okToPrint(string player, int phase) = 0;

};
#endif