#include "MapView.h"
#include "Map.h"
#include "MyObservable.h"
#include <iostream>
#include <iomanip>

MapView::MapView(MyObservable* const& observable)
{
	observable->addObserver((MyObserver*)this);
}

void MapView::update(MyObservable* observable)
{
	system("cls");

	Map* map = (Map*)observable;
	
	if (map)
	{
		int n;
		vector<Country*> countries(map->GetCountries());
		
		// TODO: Support more than 2 sets of countries
		printCountries(countries, 0, countries.size() / 2); // Print the first 5 countries
		printCountries(countries, countries.size() / 2, countries.size()); // Print the last 5 countries
	}
	
}

void MapView::printCountries(vector<Country*> countries, int start, int end)
{
	int leftPadding = 10;
	int columnWidth = 12;

	// Print the upper part of the box frame
	printColumn(218, 194, 196, 191, end - start, columnWidth, leftPadding);

	for (int j = 0; j < 6; j++)
	{
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
		}

		cout << char(179);

		for (int i = start; i < end; i++)
		{
			switch (j)
			{
			case 0:
				cout << left << setw(columnWidth) << countries[i]->getName() << char(179); //Country name
				break;
			case 1:
				cout << left << setw(columnWidth) << countries[i]->getContinent() << char(179); //Continent name
				break;
			case 2:
				cout << left << setw(columnWidth) << countries[i]->getOwnerName(columnWidth) << char(179); //Owner of the country
				break;
			case 3:
				cout << left << setw(columnWidth) << countries[i]->getNumArmies() << char(179); //number of armies
				break;
			case 4:
			case 5:
				// TODO: Refactor so that more than 2 adjacent countries are supported
				cout << left << setw(columnWidth) << countries[i]->getAdjacentCountries()[j - 4]->getName() << char(179); //Adjacent countries
				break;
			}
		}

		cout << endl;

		if (j < 4)
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
