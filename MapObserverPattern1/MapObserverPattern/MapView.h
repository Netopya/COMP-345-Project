#pragma once

#include <vector>
#include "MyObservable.h"
#include "Country.h"

using std::vector;

class MapView : public MyObserver
{
public:
	MapView(MyObservable* const& observable);
	void update(MyObservable* observable);
private:
	void printCountries(vector<Country*> countries, int start, int end);
	void printColumn(char start, char intersect, char middle, char end, int columns, int width, int padding);
};