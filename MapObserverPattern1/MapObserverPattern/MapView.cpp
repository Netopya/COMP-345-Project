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
		//string output("|");
		
		
		// TODO: Support more than 2 sets of countries
		printCountries(countries, 0, countries.size() / 2);
		printCountries(countries, countries.size() / 2, countries.size());

		/*
		for (unsigned i = countries.size() / 2; i < countries.size(); i++)
		{
			char buffer[100];
			//printf("|%5s|%5s|%5s|%5s|", arg0, arg1, arg2, arg3);
			//snprintf(buffer, sizeof(buffer), "%20s|", countries[i]->getName());
			//output += buffer;
			cout << left << setw(10) << countries[i]->getName() << '|';
		}

		cout << endl;
		*/
		//cout << output;
	}
	
}

void MapView::printCountries(vector<Country*> countries, int start, int end)
{
	int leftPadding = 10;
	int columnWidth = 12;
	//cout << setw(leftPadding) << " ";
	//cout << char(201) << std::string(64, 205) << char(187) << endl;
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
				cout << left << setw(columnWidth) << countries[i]->getName() << char(179);
				break;
			case 1:
				cout << left << setw(columnWidth) << countries[i]->getContinent() << char(179);
				break;
			case 2:
				cout << left << setw(columnWidth) << countries[i]->getOwnerName(columnWidth) << char(179);
				break;
			case 3:
				cout << left << setw(columnWidth) << countries[i]->getNumArmies() << char(179);
				break;
			case 4:
			case 5:
				// TODO: Refactor so that more than 2 adjacent countries are supported
				cout << left << setw(columnWidth) << countries[i]->getAdjacentCountries()[j - 4]->getName() << char(179);
				break;
			}
		}

		cout << endl;

		if (j < 4)
		{
			//cout << setw(leftPadding) << " ";
			//cout << char(195) << std::string(64, 196) << char(180) << endl;
			printColumn(195, 197, 196, 180, end - start, columnWidth, leftPadding);
		}
	}

	//cout << setw(leftPadding) << " ";
	//cout << char(200) << std::string(64, 205) << char(188) << endl << endl;
	printColumn(192, 193, 196, 217, end - start, columnWidth, leftPadding);
	
}

void MapView::printColumn(char start, char intersect, char middle, char end, int columns, int width, int padding)
{
	cout << setw(padding) << " ";
	cout << start;
	for (int i = 0; i < columns - 1; i++)
	{
		cout << std::string(width, middle) << intersect;
	}
	cout << std::string(width, middle) << end << endl;


}
