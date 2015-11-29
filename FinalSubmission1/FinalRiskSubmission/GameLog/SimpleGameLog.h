#ifndef SIMPLEGAMELOG_H
#define SIMPLEGAMELOG_H

#include <string>
#include <iostream>
#include <vector>
#include "..\GameLog\GameLog.h"

using namespace std;

/*
 * Base GameLog object, doesn't apply any restrictions. Game Log decorators take this class as parameter in their constructor.
 */
class SimpleGameLog : public GameLog 
{
protected:
public:
	vector<string> actions_players;
	vector<int> actions_phases;
	vector<string> actions_str;


	void LogAction(string player, int phase, string str) {
		actions_players.push_back(player);
		actions_phases.push_back(phase);
		actions_str.push_back(str);
	}
	void printLastAction() {
		cout << "Game Log:" << endl;
		switch (actions_phases.back()) {
		case 0:
			cout << "Reinforcement Phase: "<< actions_players.back() << " " << actions_str.back() << endl;
			break;
		case 1:
			cout << "Attack Phase: "<< actions_players.back() << " " << actions_str.back() << endl;
			break;
		case 2:
			cout << "Fortification Phase: " << actions_players.back() << " " << actions_str.back() << endl;
			break;

		}
	}
	bool okToPrint(string player, int phase) {
		return true;
	}

};
#endif