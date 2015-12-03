#include "World.h"

World::World(string _file)
{
	file = _file;
	continentsVector = new vector<Continent*>();
	countriesVector = new vector<Country*>();
	resetError();
}
World::World(World* _cpy)
{
	lastOperationSuccess = _cpy->lastOperationSuccess;
	lastErrorMessage = _cpy->lastErrorMessage;
	numberOfLinks = _cpy->numberOfLinks;
	continentsVector = _cpy->continentsVector;
	countriesVector = _cpy->countriesVector;
}


World::World()
{
	file = "default";
	continentsVector = new vector<Continent*>();
	countriesVector = new vector<Country*>();
	resetError();
}

bool World::addContinent(const char* _name, int _controlValue)
{
	resetError();
	//We cannot allow 2 times the same name.
	if (getContinentFromName(_name) != NULL)
	{
		setError("The continent already exists.");
		return false;
	}
	//Create the object with a +1 registry Value.
	Continent* continentObject = new Continent(_name, (int)continentsVector->size(), _controlValue);
	//Once we have the infos of one, we add it to our vector.
	continentsVector->push_back(continentObject);
	return true;
}
bool World::addCountry(const char* _name, const char* _continent)
{
	resetError();
	//We cannot allow 2 times the same name.
	if (getCountryFromName(_name) != NULL)
	{
		setError("The country already exists.");
		return false;
	}

	Continent* continent = getContinentFromName(_continent);

	if (continent == NULL)
	{
		setError("The continent does not exists.");
		return false;
	}

	//Create the object.
	Country* countryObject = new Country(_name, (int)countriesVector->size());
	countryObject->setContinent(continent);

	//Once we have the infos of one, we add it to our vector.
	countriesVector->push_back(countryObject);
	return true;
}
bool World::addLink(const char* _country, vector<const char*>* linkedCountries)
{
	resetError();
	Country* country = this->getCountryFromName(_country);
	if (country == NULL)
	{
		setError("The country does not exists.");
		return false;
	}

	Country* tmp = NULL;
	vector<Country*>* linksVector = new vector<Country*>();
	for (int i = 0; i < linkedCountries->size(); i++)
	{
		tmp = getCountryFromName(linkedCountries->at(i));

		if (tmp == country)
		{
			setError("Cannot link country to itself.");
			return false;
		}

		if (tmp) linksVector->push_back(tmp);
		else
		{
			setError("One of the linked countries does not exists.");
			return false;
		}
	}

	country->connect(linksVector);

	//Important: two-ways connection. Bidirectionnal.
	for (int i = 0; i < linksVector->size(); i++)
		linksVector->at(i)->connect(country);

	numberOfLinks++;
	return true;
}

bool World::checkLastOperationSuccess()
{
	return lastOperationSuccess;
}
const char* World::getLastErrorMessage()
{
	return (lastErrorMessage) ? lastErrorMessage : "No errors.";
}	
void World::setError(const char * _message) 
{
	lastErrorMessage = _message;
	lastOperationSuccess = false;
}
void World::resetError() 
{
	lastErrorMessage = NULL;
	lastOperationSuccess = true;
}

/*
* Reversed operation of what happened within analyseFile().
* Please see analyseFile() for more information.
*/
bool World::toFile()
{
	setError("Acessing pure virtual function.");
	return false;
}

vector<Country*>* World::getCountries()
{
	return countriesVector;
}

vector<Continent*>* World::getContinents()
{
	return continentsVector;
}

Continent* World::getContinentFromName(string _name)
{
	for (int i = 0; i < continentsVector->size(); i++)
		if (continentsVector->at(i)->getName().compare(_name) == 0)
			return continentsVector->at(i);
	return NULL;
}
Country* World::getCountryFromName(string _name)
{
	for (int i = 0; i < countriesVector->size(); i++)
		if (countriesVector->at(i)->getName().compare(_name) == 0)
			return countriesVector->at(i);
	return NULL;
}

bool World::validPlayerPath(Country* from, Country* to, Player* player)
{
	//Perform a recursive Depth First Search to determine if there is a valid path.
	vector<Country*>* visited = new vector<Country*>();
	visited->push_back(from);
	bool valid = validPlayerPath(*(from->getConnectedCountries()), visited, to, player);
	delete visited;
	return valid;
}

bool World::validPlayerPath(vector<Country*> investigate, vector<Country*>* visited, Country* goal, Player* player)
{
	for (unsigned int i = 0; i < investigate.size(); i++)
	{
		if (investigate[i] == goal)
		{
			return true; //We've found the requested country.
		}
		else if (investigate[i]->getControllingPlayer() != player)
		{
			continue; //Ignore countries not owned by the player.
		}

		bool bvisited = false;
		for (unsigned int j = 0; j < visited->size(); j++)
		{
			if (visited->at(j) == investigate[i])
			{
				bvisited = true;
				break;
			}
		}

		//If we haven't checkout this country, add it to the list of visited countries and investigate its adjacent countries.
		if (!bvisited)
		{
			visited->push_back(investigate[i]);
			bool foundPath = validPlayerPath(*(investigate[i]->getConnectedCountries()), visited, goal, player);
			if (foundPath)
			{
				return true;
			}
		}
	}

	return false;
}

/*
	* Returns true if it has successfully loaded all the lines from _inputFile
	* without encoutering ANY format or syntax error into our parameters.
	* FOR MORE INFORMATION ABOUT THE FORMAT OF THE FILE, PLEASE TAKE A LOOK AT World.txt.
	*/
bool World::fromFile()
{
	setError("Acessing pure virtual function.");
	return false;
}
string World::getFile()
{
	return file;
}
