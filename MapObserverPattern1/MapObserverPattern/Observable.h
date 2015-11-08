#pragma once

#include <vector>
#include "Observer.h"

class MyObservable {
private:
	std::vector<MyObserver*> observers;

public:
	void addObserver(MyObserver* const& observer);
	void notifyObservers();
};