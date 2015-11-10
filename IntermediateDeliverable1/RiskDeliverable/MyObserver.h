#pragma once

/*
Michael Bilinsky 26992358
COMP 345 Assignment #2 - Part 2: Map Observer Pattern

Observer Interface for the Observer Pattern
*/

class MyObserver {
public:
	virtual void update(class MyObservable* observable) = 0; // Called when being notified of a change from the observable
};