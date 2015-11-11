#pragma once

#include "MyObserver.h";

class PlayerView : public MyObserver {
public:
	PlayerView(MyObservable* const& observable);
	void update(MyObservable* observable); // Override
};