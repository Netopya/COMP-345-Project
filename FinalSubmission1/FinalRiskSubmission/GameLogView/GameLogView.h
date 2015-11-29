#ifndef GAMELOGVIEW_H
#define GAMELOGVIEW_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <math.h>

#include "..\GameLog\GameLog.h"
#include "..\MyObservable\MyObservable.h"

/*
 * Observer game log view outputs last validated log entry.
 * it gets notified of a change.
 */
class GameLogView : public MyObserver
{
public:
	GameLogView(MyObservable* const& observable);
	void update(MyObservable* observable);
private:

};
#endif