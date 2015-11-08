#include "MapView.h"
#include "Map.h"
#include "Observable.h"
#include <iostream>

MapView::MapView(MyObservable* const& observable)
{
	observable->addObserver(this);
}

void MapView::update(MyObservable * observable)
{
	Map* map = (Map*)observable;
	
	if (map)
	{
		int n;
		vector<Country*> countries(map->GetCountries());
		string output("|");
		for (unsigned i = 0; i < countries.size(); i++)
		{
			char buffer[100];
			//printf("|%5s|%5s|%5s|%5s|", arg0, arg1, arg2, arg3);
			snprintf(buffer, sizeof(buffer), "%5s|", countries[i]->getName());
			output += buffer;
		}

		cout << output;
	}
	
}
