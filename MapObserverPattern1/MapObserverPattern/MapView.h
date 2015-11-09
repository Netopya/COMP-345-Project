#pragma once

/*
Michael Bilinsky 26992358
COMP 345 Assignment #2 - Part 2: Map Observer Pattern

Observer Map view outputs a table of the map when it gets notified of a change
*/

#include <vector>
#include "MyObservable.h"
#include "Country.h"

using std::vector;

class MapView : public MyObserver
{
public:
	MapView(MyObservable* const& observable);
	void update(MyObservable* observable); // Override
private:
	void printCountries(vector<Country*> countries, int start, int end); // Print all the countries to the console
	void printColumn(char start, char intersect, char middle, char end, int columns, int width, int padding); // Print a horizontal line of box formatting
};