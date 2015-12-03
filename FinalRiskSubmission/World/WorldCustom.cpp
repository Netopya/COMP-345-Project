#include "WorldCustom.h"

WorldCustom::WorldCustom() : World()
{
}
WorldCustom::WorldCustom(World* _cpy) : World(_cpy)
{
	this->file = _cpy->getFile().substr(0, _cpy->getFile().size() - 4) + ".txt";
}
WorldCustom::WorldCustom(string _file) : World(_file)
{
}

bool WorldCustom::fromFile()
{
	cout << "From file: " << file << endl;
	resetError();
	Reader* reader = new Reader(file.c_str());
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
				char* continentInfo;
				int* registryValue;
				int* controlValue;
				//We want to put in memory the name of it until an '=' an then its reference value (a.k.a. registryValue).
				reader->getMultipleFormats("%l==%u,%u\n", &continentInfo, &registryValue, &controlValue);
				Continent* continentObject = new Continent(continentInfo, *registryValue, *controlValue);
				//Once we have the infos of one, we add it to our vector.
				continentsVector->push_back(continentObject);
			}

			//Look for the first parameter: the countries.
			reader->flushUntilYou('[');
			reader->getMultipleFormats("[Territories=%u]\n", &valueQuantity);
			if (*valueQuantity == 0)
			{
				setError("No countries.");
				reader->Close();
				return false;
			}


			//For every country.
			for (int i = 0; i < *valueQuantity; i++)
			{
				char* countryInfo;
				int* registryValue;
				//We want to put in memory the name of it until an '=' an then its reference value (a.k.a. registryValue).
				reader->getMultipleFormats("%l==%u\n", &countryInfo, &registryValue);
				Country* countryObject = new Country(countryInfo, *registryValue);
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
				//We first select the country we want to link, and then we load its related cartesian position and continent and put then into several variables.
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
			setError(fng.what());
			return false;
		}
		//Syntax error: better stop operation as soon as possible.
		catch (FormatSyntax fs) {
			setError(fs.what());
			return false;
		}
		//Close the file whatever happened not to loose data.
		reader->Close();
		return true;
	}
	else
		setError("Could not open the input file.");
	return false;
}

bool WorldCustom::toFile()
{
	cout << "To file: " << file << endl;
	resetError();
	Writer* writer = new Writer(file.c_str());
	if (writer && writer->Open())
	{
		try
		{
			writer->writeMultipleFormats("[Continents=%u]\n", continentsVector->size());
			for (int i = 0; i < continentsVector->size(); i++)
				writer->writeMultipleFormats("%n=%u,%u\n", continentsVector->at(i)->getName(), continentsVector->at(i)->getRegistryValue(), continentsVector->at(i)->getControlValue());
			//cout << countriesVector->at(0)->getName();
			//cout << continentsVector->at(0)->getName();
			writer->writeMultipleFormats("[Territories=%u]\n", countriesVector->size());
			for (int i = 0; i < countriesVector->size(); i++)
				writer->writeMultipleFormats("%n=%u\n", countriesVector->at(i)->getName().c_str(), countriesVector->at(i)->getRegistryValue());
			writer->writeMultipleFormats("[Links=%u]\n", numberOfLinks);
			for (int i = 0, j = 0; i < (int)countriesVector->size(); i++)
			{
				writer->writeMultipleFormats("%u,%u,%u,%u,", countriesVector->at(i)->getRegistryValue(), countriesVector->at(i)->getPositionX(), countriesVector->at(i)->getPositionY(), countriesVector->at(i)->getContinent()->getRegistryValue());
				for (j = 0; j < (int)countriesVector->at(i)->getConnectedCountries()->size(); j++)
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
			setError(dng.what());
			return false;
		}
		//File does not respond.
		catch (fileNotGood fng) {
			setError(fng.what());
			return false;
		}
		//Close the file whatever happened not to loose data.
		writer->Close();

		return true;
	}
	else
		setError("Could not open the output file.");
	return false;
}