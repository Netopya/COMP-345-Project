#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <stdarg.h> 
#include <algorithm>
#include <exception>

#include "Continent.h"
#include "Country.h"
#include "..\Reader\Reader.h"
#include "..\Writer\Writer.h"
#include "..\Player\Player.h"
#include "..\MyObservable\MyObservable.h"

using namespace std;

/*
 * Holds all the necessary information about the countries and the continents
 * of a typical risk game.
 */
class World : public MyObservable
{
	friend class TwoWayFileFormatAdapter;
protected:

	string file;
	const char* lastErrorMessage;
	bool lastOperationSuccess;
	int numberOfLinks;
	//Contains the adresses of all the continents from this map.
	vector<class Continent*>* continentsVector;
	//Contains the adresses of all the countries from this map.
	vector<class Country*>* countriesVector;
	void setError(const char *);
	void resetError();


public:
	/*
	 * Constructor which immediately loads the input file when called.
	 */
	World();
	World(string);
	World(class World*);

	bool addContinent(const char* _name, int _controlValue);
	bool addCountry(const char* _name, const char* _continent);
	bool addLink(const char* _country, vector<const char*>* linkedCountries);
	bool checkLastOperationSuccess();
	const char* getLastErrorMessage();

	/*
	 * Reversed operation of what happened within analyseFile().
	 * Please see fromFile() for more information.
	 */
	virtual bool toFile();
	/*
	* Returns true if it has successfully loaded all the lines from _inputFile
	* without encoutering ANY format or syntax error into our parameters.
	* FOR MORE INFORMATION ABOUT THE FORMAT OF THE FILE, PLEASE TAKE A LOOK AT World.txt.
	*/
	virtual bool fromFile();

	vector<Country*>* getCountries();

	vector<Continent*>* getContinents();

	Continent* getContinentFromName(string _name);
	Country* getCountryFromName(string _name);
	bool validPlayerPath(class Country* from, class Country* to, class Player* player);

private:
	bool validPlayerPath(vector<Country*> investigate, vector<Country*>* visited, Country* goal, Player* player);



public:

	string getFile();
};
#endif