#include "MapView.h"
#include "World/World.h"
#include "MyObservable.h"
#include <iostream>
#include <iomanip>
#include <math.h>

MapView::MapView(MyObservable* const& observable)
{
	observable->addObserver((MyObserver*)this);

	editorMode = false;
}

void MapView::update(MyObservable* observable)
{
	system("cls");

	World* map = (World*)observable;
	
	if (map)
	{
		// Calculate the number of rows
		int n;
		vector<Country*> countries(*(map->getCountries()));
		int numCountries = countries.size();
		int rows = ceil(numCountries / (float)MAX_COLUMNS);

		for (int i = 0; i < rows; i++)
		{
			// calculate the number of columns, usually max except at the last column
			printCountries(countries, i * MAX_COLUMNS, min((i+1) * MAX_COLUMNS, numCountries));
		}
	}
	
}

void MapView::setEditorMode(bool editorMode)
{
	this->editorMode = editorMode;
}

void MapView::printCountries(vector<Country*> countries, int start, int end)
{
	int leftPadding = 10;
	int columnWidth = 12;

	// Print the upper part of the box frame
	printColumn(218, 194, 196, 191, end - start, columnWidth, leftPadding);

	int maxNumAdjacentCountries = 0;

	// Calculate the maximum number of adjacent countries out of all the countries in this row
	for (int i = start; i < end; i++)
	{
		if (countries[i]->getConnectedCountries()->size() > maxNumAdjacentCountries)
		{
			maxNumAdjacentCountries = countries[i]->getConnectedCountries()->size();
		}
	}


	for (int j = 0; j < 4 + maxNumAdjacentCountries; j++)
	{
		if (editorMode && j > 1 && j < 4)
		{
			continue; // Don't show all the information if in the map editor
		}

		switch(j)
		{
			case 0:
				cout << right << setw(leftPadding) << "Country";
				break;
			case 1:
				cout << right << setw(leftPadding) << "Continent";
				break;
			case 2:
				cout << right << setw(leftPadding) << "Owner";
				break;
			case 3:
				cout << right << setw(leftPadding) << "Armies";
				break;
			case 4:
				cout << right << setw(leftPadding) << "Adjecent";
				break;
			case 5:
				cout << right << setw(leftPadding) << "Countries";
				break;
			default:
				cout << right << setw(leftPadding) << std::string(leftPadding, ' ');
		}

		cout << char(179);

		for (int i = start; i < end; i++)
		{
			switch (j)
			{
			case 0:
				cout << left << setw(columnWidth) << truncateChar(countries[i]->getName(), columnWidth) << char(179); //Country name
				break;
			case 1:
				cout << left << setw(columnWidth) << truncateChar(countries[i]->getContinent()->getName(), columnWidth) << char(179); //Continent name
				break;
			case 2:
				cout << left << setw(columnWidth) << countries[i]->getControllingPlayer()->GetPlayerName(columnWidth) << char(179); //Owner of the country
				break;
			case 3:
				cout << left << setw(columnWidth) << countries[i]->getNumArmies() << char(179); //number of armies
				break;
			}

			if (j > 3)
			{
				if ((j - 4) < countries[i]->getConnectedCountries()->size())
				{
					cout << left << setw(columnWidth) << truncateChar((*(countries[i]->getConnectedCountries()))[j - 4]->getName(), columnWidth) << char(179); //Adjacent countries
				}
				else
				{
					// Print empty space if the country has no more adjacent countries to print out
					cout << left << setw(columnWidth) << std::string(columnWidth, ' ') << char(179);
				}
				
			}
		}

		cout << endl;

		if (j < 4) // Not between adjacent countries
		{
			// Print a box section between rows
			printColumn(195, 197, 196, 180, end - start, columnWidth, leftPadding);
		}
	}

	// Print the lower part of the box frame
	printColumn(192, 193, 196, 217, end - start, columnWidth, leftPadding);
	
}

void MapView::printColumn(char start, char intersect, char middle, char end, int columns, int width, int padding)
{
	// Set the left padding
	cout << setw(padding) << " ";

	// The leftmost box frame element
	cout << start;

	// For each column except the last one, fill with the middle character and then place the character that indicated the middle between rows
	for (int i = 0; i < columns - 1; i++)
	{
		cout << std::string(width, middle) << intersect;
	}

	// Print the last column fill and the rightmost box frame element
	cout << std::string(width, middle) << end << endl;


}

string MapView::truncateChar(const char* input, int max)
{
	string output(input);
	return output.substr(0, max);
}