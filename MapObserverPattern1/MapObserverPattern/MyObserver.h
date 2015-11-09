#pragma once
class MyObserver {
public:
	virtual void update(class MyObservable* observable) = 0;
};