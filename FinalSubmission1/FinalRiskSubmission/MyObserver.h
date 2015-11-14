#pragma once

/*

Observer Interface for the Observer Pattern
*/

class MyObserver {
public:
	virtual void update(class MyObservable* observable) = 0; // Called when being notified of a change from the observable
};