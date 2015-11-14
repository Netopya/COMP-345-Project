#pragma once

#include "MyObserver.h";

/*
Player observer that displays player information on the console
*/
class PlayerView : public MyObserver {
public:
	PlayerView(MyObservable* const& observable);
	void update(MyObservable* observable); // Override
};