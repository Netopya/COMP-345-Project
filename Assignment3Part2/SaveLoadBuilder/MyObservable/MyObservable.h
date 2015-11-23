#ifndef MYOBSERVABLE_H
#define MYOBSERVABLE_H

#include <iostream>
#include <string>
#include <vector>
#include "MyObserver.h"

using namespace std;

/*
 * Observable super class for the Observer Pattern.
 */
class MyObservable {
private:
	std::vector<MyObserver*> observers;

public:
	void addObserver(MyObserver* const& observer);
	void notifyObservers();
};
#endif