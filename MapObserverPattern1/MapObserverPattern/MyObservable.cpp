#include "MyObservable.h"

void MyObservable::addObserver(MyObserver* const& observer)
{
	observers.push_back(observer);
}

void MyObservable::notifyObservers()
{
	for (unsigned i = 0; i < observers.size(); i++)
	{
		observers[i]->update(this);
	}
}
