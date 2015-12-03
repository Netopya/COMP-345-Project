#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <math.h>

#include "..\World\World.h"
#include "..\MyObservable\MyObservable.h"

/*
 * Observer Map view outputs a table of the map when
 * it gets notified of a change.
 */
class MapView : public MyObserver
{
public:
	MapView(MyObservable* const& observable);
	void update(MyObservable* observable);
	void setEditorMode(bool);

private:
	const int MAX_COLUMNS = 5;
	bool editorMode;
	/*
	 * Print all the countries to the console in a table.
	 */
	void printCountries(std::vector<class Country*> countries, int start, int end);
	/*
	 * Print a horizontal line of box formatting.
	 */
	void printColumn(int start, int intersect, int middle, int end, int columns, int width, int padding);

	std::string truncateChar(const char* input, int max);
};
#endif