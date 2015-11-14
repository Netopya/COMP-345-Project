#pragma once

#include "../MyObservable.h"
#include "../Lib.h"
/*
 * Holds all the necessary information about the countries and the continents
 * of a typical risk game.
 */
class World : public MyObservable
{
	const char* inputFile;
	const char* lastErrorMessage;
	bool lastOperationSuccess;
	int numberOfLinks;
	//Contains the adresses of all the continents from this map.
	vector<Continent*>* continentsVector;
	//Contains the adresses of all the countries from this map.
	vector<Country*>* countriesVector;

public:
	/*
	 * Constructor which immediately loads the input file when called.
	 */
	World(const char* _inputFile)
	{
		inputFile = _inputFile;
		lastErrorMessage = NULL;
		continentsVector = new vector<Continent*>();
		countriesVector = new vector<Country*>();
		lastOperationSuccess = analyseFile();
	}

	bool addContinent(const char* _name)
	{
		lastOperationSuccess = true;
		//We cannot allow 2 times the same name.
		if (getContinentFromName(_name) != NULL)
		{
			lastOperationSuccess = false;
			lastErrorMessage = "The continent already exists.";
			return false;
		}
		//Create the object with a +1 registry Value.
		Continent* continentObject = new Continent(_name, continentsVector->size());
		//Once we have the infos of one, we add it to our vector.
		continentsVector->push_back(continentObject);
		return true;
	}
	bool addCountry(const char* _name, const char* _continent)
	{
		lastOperationSuccess = true;
		//We cannot allow 2 times the same name.
		if (getCountryFromName(_name) != NULL)
		{
			lastOperationSuccess = false;
			lastErrorMessage = "The country already exists.";
			return false;
		}

		Continent* continent = getContinentFromName(_continent);

		if (continent == NULL)
		{
			lastOperationSuccess = false;
			lastErrorMessage = "The continent does not exists.";
			return false;
		}

		//Create the object.
		Country* countryObject = new Country(_name, countriesVector->size());
		countryObject->setContinent(continent);

		//Once we have the infos of one, we add it to our vector.
		countriesVector->push_back(countryObject);
		return true;
	}
	bool addLink(const char* _country, vector<const char*>* linkedCountries)
	{
		lastOperationSuccess = true;
		Country* country = this->getCountryFromName(_country);
		if (country == NULL)
		{
			lastOperationSuccess = false;
			lastErrorMessage = "The country does not exists.";
			return false;
		}

		Country* tmp = NULL;
		vector<Country*>* linksVector = new vector<Country*>();
		for (int i = 0; i < linkedCountries->size(); i++)
		{
			tmp = getCountryFromName(linkedCountries->at(i));

			if (tmp == country)
			{
				lastOperationSuccess = false;
				lastErrorMessage = "Cannot link country to itself.";
				return false;
			}

			if (tmp) linksVector->push_back(tmp);
			else
			{
				lastOperationSuccess = false;
				lastErrorMessage = "One of the linked countries does not exists.";
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

	bool checkLastOperationSuccess()
	{
		return lastOperationSuccess;
	}
	const char* getLastErrorMessage()
	{
		return (lastErrorMessage) ? lastErrorMessage : "No errors.";
	}

	/*
	 * Reversed operation of what happened within analyseFile().
	 * Please see analyseFile() for more information.
	 */
	bool toFile(const char* _outputFile)
	{
		lastOperationSuccess = false;
		Writer* writer = new Writer(_outputFile);
		if (writer && writer->Open())
		{
			try
			{
				writer->writeMultipleFormats("[Continents=%u]\n", continentsVector->size());
				for (int i = 0; i < continentsVector->size(); i++)
					writer->writeMultipleFormats("%n=%u\n", continentsVector->at(i)->getName(), continentsVector->at(i)->getRegistryValue());
				writer->writeMultipleFormats("[Territories=%u]\n", countriesVector->size());
				for (int i = 0; i < countriesVector->size(); i++)
					writer->writeMultipleFormats("%n=%u\n", countriesVector->at(i)->getName(), countriesVector->at(i)->getRegistryValue());
				writer->writeMultipleFormats("[Links=%u]\n", numberOfLinks);
				for (int i = 0, j = 0; i < countriesVector->size(); i++)
				{
					writer->writeMultipleFormats("%u,%u,%u,%u,", countriesVector->at(i)->getRegistryValue(), countriesVector->at(i)->getPositionX(), countriesVector->at(i)->getPositionY(), countriesVector->at(i)->getContinent()->getRegistryValue());
					for (j = 0; j < countriesVector->at(i)->getConnectedCountries()->size(); j++)
					{
						writer->writeNextPosSignedINT32(countriesVector->at(i)->getConnectedCountries()->at(j)->getRegistryValue());
						if (j == countriesVector->at(i)->getConnectedCountries()->size() - 1)
							writer->writeNextByte('\n');
						else
							writer->writeNextByte(',');
					}
				}
				writer->writeNextByte('\n');
			}
			//The data sent to the writer was corrupted.
			catch (DataNotGood dng) {
				lastErrorMessage = dng.what();
				return false;
			}
			//File does not respond.
			catch (fileNotGood fng) {
				lastErrorMessage = fng.what();
				return false;
			}
			//Close the file whatever happened not to loose data.
			writer->Close();
			
			lastOperationSuccess = true;
			return true;
		}
		else
			lastErrorMessage = "Could not open the output file.";
		return false;
	}

	vector<Country*>* getCountries()
	{
		return countriesVector;
	}

	vector<Continent*>* getContinents()
	{
		return continentsVector;
	}

	Continent* getContinentFromName(const char* _name)
	{
		for (int i = 0; i < continentsVector->size(); i++)
			if (strcmp(continentsVector->at(i)->getName(), _name) == 0)
				return continentsVector->at(i);
		return NULL;
	}
	Country* getCountryFromName(const char* _name)
	{
		for (int i = 0; i < countriesVector->size(); i++)
			if (strcmp(countriesVector->at(i)->getName(), _name) == 0)
				return countriesVector->at(i);
		return NULL;
	}

	bool validPlayerPath(Country* from, Country* to, Player* player)
	{
		// Perform a recursive Depth First Search to determine if there is a valid path
		vector<Country*>* visited = new vector<Country*>();
		visited->push_back(from);
		bool valid = validPlayerPath(*(from->getConnectedCountries()), visited, to, player);
		delete visited;
		return valid;
	}

private:
	bool validPlayerPath(vector<Country*> investigate, vector<Country*>* visited, Country* goal, Player* player)
	{
		for (unsigned int i = 0; i < investigate.size(); i++)
		{
			if (investigate[i] == goal)
			{
				return true; // We've found the requested country
			}
			else if (investigate[i]->getControllingPlayer() != player)
			{
				continue; //Ignore countries not owned by the player
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

			// If we haven't checkout this country, add it to the list of visited countries and investigate its adjacent countries
			if (!bvisited)
			{
				visited->push_back(investigate[i]);
				return validPlayerPath(*(investigate[i]->getConnectedCountries()), visited, goal, player);
			}
		}

		return false;
	}

	/*
	 * Returns true if it has successfully loaded all the lines from _inputFile
	 * without encoutering ANY format or syntax error into our parameters.
	 * FOR MORE INFORMATION ABOUT THE FORMAT OF THE FILE, PLEASE TAKE A LOOK AT World.txt.
	 */
	bool analyseFile()
	{
		Reader* reader = new Reader(inputFile);
		if (reader && reader->Open())
		{
			try
			{
				//Keeps in memory the number of loops we currently have to do.
				int* valueQuantity;

				//Look for the first parameter: the continents.
				reader->flushUntilYou('[');
				reader->getMultipleFormats("[Continents=%u]\n", &valueQuantity);

				//For every continent.
				for (int i = 0; i < *valueQuantity; i++)
				{			
					s32data* continentInfo;
					int* registryValue;
					//We want to put in memory the name of it until an '=' an then its reference value (a.k.a. registryValue).
					reader->getMultipleFormats("%l==%u\n", &continentInfo, &registryValue);
					Continent* continentObject = new Continent(continentInfo->bin, *registryValue);
					//Once we have the infos of one, we add it to our vector.
					continentsVector->push_back(continentObject);
				}
				
				//Look for the first parameter: the countries.
				reader->flushUntilYou('[');
				reader->getMultipleFormats("[Territories=%u]\n", &valueQuantity);

				//For every country.
				for (int i = 0; i < *valueQuantity; i++)
				{				
					s32data* countryInfo;
					int* registryValue;		
					//We want to put in memory the name of it until an '=' an then its reference value (a.k.a. registryValue).
					reader->getMultipleFormats("%l==%u\n", &countryInfo, &registryValue);
					Country* countryObject = new Country(countryInfo->bin, *registryValue);
					//Once we have the infos of one, we add it to our vector.
					countriesVector->push_back(countryObject);
				}
				
				//Look for the first parameter: the links between continents.
				reader->flushUntilYou('[');
				reader->getMultipleFormats("[Links=%u]\n", &valueQuantity);
				numberOfLinks = *valueQuantity;

				//For every link.
				for (int i = 0; i < *valueQuantity; i++)
				{				
					int *countryRegistryValue, *continentRegistryValue, *countryPositionX, *countryPositionY;
					int** countryLinks = new int*[10]; //We eventually won't need more than 10 spaces.
					/*
					 * We first select the country we want to link, and then we load its related cartesian position
					 * and continent and put then into several variables.
					 */
					reader->getMultipleFormats("%u,%u,%u,%u", &countryRegistryValue, &countryPositionX, &countryPositionY, &continentRegistryValue);
					vector<Country*>* linksVector = new vector<Country*>();
					//Then, as long as the line does not end, we take the values of the linked countries.
					for (int j = 0; reader->byteAtActualPosition() != '\n'; j++)
					{
						if (j > 9) break;
						reader->getMultipleFormats(",%u", &countryLinks[j]);
						linksVector->push_back(countriesVector->at(*countryLinks[j]));
					}
					//Flush the '\n' meaning that we are ready for the next line to be loaded.
					reader->flushNextByte();

					//Set all the infos we just loaded to its proper country.
					countriesVector->at(*countryRegistryValue)->setCartesian(*countryPositionX, *countryPositionY);
					countriesVector->at(*countryRegistryValue)->setContinent(continentsVector->at(*continentRegistryValue));
					countriesVector->at(*countryRegistryValue)->connect(linksVector);
				}
			}
			//File does not respond.
			catch (fileNotGood fng) {
				lastErrorMessage = fng.what();
				return false;
			}
			//Syntax error: better stop operation as soon as possible.
			catch (FormatSyntax fs) {
				lastErrorMessage = fs.what();
				return false;
			}
			//Close the file whatever happened not to loose data.
			reader->Close();
			return true;
		}
		else
			lastErrorMessage = "Could not open the input file.";
		return false;
	}
};