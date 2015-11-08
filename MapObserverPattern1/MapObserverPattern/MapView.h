#pragma once
#include "Observer.h"
#include "Observable.h"

class MapView : public MyObserver
{
	MapView(MyObservable* const& observable);
	void update(MyObservable* observable);
};