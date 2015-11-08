#pragma once

#include "Observable.h"

class MyObserver {
public:
	virtual void update(MyObservable* const& observable) = 0;	
};