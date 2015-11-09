#pragma once

#include <vector>
#include "MyObserver.h"

class MyObservable {
private:
	

	std::vector<MyObserver*> observers;

public:
	void addObserver(MyObserver* const& observer);
	void notifyObservers();
};