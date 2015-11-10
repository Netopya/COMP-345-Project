#pragma once

/*
Michael Bilinsky 26992358
COMP 345 Assignment #2 - Part 2: Map Observer Pattern

Observable super class for the Observer Pattern
*/

#include <vector>
#include "MyObserver.h"

class MyObservable {
private:
	std::vector<MyObserver*> observers;

public:
	void addObserver(MyObserver* const& observer);
	void notifyObservers();
};