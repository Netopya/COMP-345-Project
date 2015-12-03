#include "WorldConquest.h"

WorldConquest::WorldConquest() : World()
{
}
WorldConquest::WorldConquest(World* _cpy) : World(_cpy)
{
	this->file = _cpy->getFile().substr(0, _cpy->getFile().size() - 4) + ".map";
}
WorldConquest::WorldConquest(string _file) : World(_file)
{
}

bool WorldConquest::fromFile()
{
	cout << "From file: " << file << endl;
	resetError();
	Reader* reader = new Reader(file.c_str());
	if (reader && reader->Open())
	{
		bool safeEndFile = false;
		vector<string> lines;
		vector<int> x;
		vector<int> y;
		vector<string> countries;
		vector<string> continents;

		try
		{
			//Flushes the [Map] section we do not need.
			reader->flushNextByte();
			reader->flushUntilYou('[');

			//Gets the continent section.
			reader->getMultipleFormats("[Continents]\n");
			int registryValueContinent = 0;
			//For every continent. Since we don't know the number of continents, we wait for the carriage return.
			while (reader->byteAtActualPosition() != '\n')
			{
				char* continentInfo;
				int* controlValue;
				//We want to put in memory the name of it until an '=' an then its reference value (a.k.a. registryValue).
				reader->getMultipleFormats("%l==%u\n", &continentInfo, &controlValue);
				Continent* continentObject = new Continent(continentInfo, registryValueContinent, *controlValue);
				//Once we have the infos of one, we add it to our vector.
				continentsVector->push_back(continentObject);
				registryValueContinent++;
			}

			//Flushes the next carriage return. 
			reader->flushNextByte();

			//Gets the continent section.
			reader->getMultipleFormats("[Territories]\n");

			safeEndFile = true;

			while (1)
			{
				string tmp = reader->getNextLine();
				//cout << tmp << endl;
				if (tmp != "")
					lines.push_back(tmp);
			}
		}
		catch (fileNotGood fng)
		{
			if (safeEndFile == false)
			{
				setError(fng.what());
				return false;
			}
		}
		catch (FormatSyntax fs)
		{
			setError(fs.what());
			return false;
		}
		//Getting the country.
		getString(lines, countries);
		if (countries.size() == 0)
		{
			setError("No countries.");
			reader->Close();
			return false;
		}
		//Getting the x.
		getNumber(lines, x);
		//Getting the x.
		getNumber(lines, y);
		//Getting the country.
		getString(lines, continents);
		//Getting the adjacent countries.
		vector<string>* links = new vector<string>[countries.size()];
		for (size_t i = 0; i < countries.size(); i++)
		{
			//Getting the links.
			if (getLinks(lines.at(i), links[i]) == false)
				return false;
		}

		for (size_t i = 0; i < countries.size(); i++)
		{
			Country* countryObject = new Country(countries.at(i).c_str(), i);
			countriesVector->push_back(countryObject);
			//cout << countries.at(i).c_str() << endl;
		}

		for (size_t i = 0; i < countriesVector->size(); i++)
		{
			vector<Country*>* linksVector = new vector<Country*>();

			//cout << "Links" << endl;
			for (size_t j = 0; j < links[i].size(); j++)
			{
				Country* tmp = getCountryFromName(links[i].at(j).c_str());
				linksVector->push_back(tmp);
			}
			countriesVector->at(i)->setCartesian(x.at(i), y.at(i));
			countriesVector->at(i)->setContinent(getContinentFromName(continents.at(i).c_str()));
			countriesVector->at(i)->connect(linksVector);
		}
		numberOfLinks = countriesVector->size();
	}
	return true;
}

bool WorldConquest::toFile()
{
	cout << "To file: " << file << endl;
	resetError();
	Writer* writer = new Writer(file.c_str());
	if (writer && writer->Open())
	{
		try
		{
			writer->writeNextArray("[Map]\nauthor=420BlazeItMLGNoscope\n\n");
			writer->writeMultipleFormats("[Continents]\n");
			for (int i = 0; i < continentsVector->size(); i++)
				writer->writeMultipleFormats("%n=%u\n", continentsVector->at(i)->getName(), continentsVector->at(i)->getControlValue());
			writer->writeMultipleFormats("[Territories]\n");
			for (int i = 0, j = 0; i < (int)countriesVector->size(); i++)
			{
				/*
				for (int i = 0; i < countriesVector->size(); i++)
				writer->writeMultipleFormats("%n=%u\n", countriesVector->at(i)->getName().c_str(), countriesVector->at(i)->getRegistryValue());
				writer->writeMultipleFormats("[Links=%u]\n", numberOfLinks);
				*/
				writer->writeMultipleFormats("%n,%u,%u,%n,", countriesVector->at(i)->getName().c_str(), countriesVector->at(i)->getPositionX(), countriesVector->at(i)->getPositionY(), countriesVector->at(i)->getContinent()->getName());
				for (j = 0; j < (int)countriesVector->at(i)->getConnectedCountries()->size(); j++)
				{
					writer->writeNextArray(countriesVector->at(i)->getConnectedCountries()->at(j)->getName().c_str());
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
		setError("Could not open the output file.");
	return false;
}
bool WorldConquest::getLinks(string _line, vector<string>& _links)
{
	while (_line != "")
	{
		int pos = _line.find(',');
		if (pos == std::string::npos)
		{
			pos = _line.size();
		}
		//cout << _line.substr(0, pos) << endl;
		_links.push_back(_line.substr(0, pos));
		if (pos != _line.size())
			_line = _line.substr(pos + 1, _line.size());
		else
			_line = "";
		//cout << _line << endl;

	}
	return true;
}
bool WorldConquest::getString(vector<string>& _lines, vector<string>& _string)
{
	for (size_t i = 0; i < _lines.size(); i++)
	{	
		//We finished to analyse this line
		//cout << ":" << _lines.at(i) << ":" << endl;
		if (_lines.at(i) == "")
			continue;
		int pos = _lines.at(i).find(',');
		if (pos == std::string::npos)
		{
			pos = _lines.at(i).size();
		}
		//cout << _lines.at(i).substr(0, pos) << endl;
		_string.push_back(_lines.at(i).substr(0, pos));
		if (pos != _lines.at(i).size())
			_lines.at(i) = _lines.at(i).substr(pos + 1, _lines.at(i).size());
		else
			_lines.at(i) = "";
		//cout << _lines.at(i) << endl;
		
	}
	return true;
}
bool WorldConquest::getNumber(vector<string>& _lines, vector<int>& _numbers)
{
	//Getting the y value.
	for (size_t i = 0; i < _lines.size(); i++)
	{
		//cout << _lines.at(i) << endl;
		int pos = _lines.at(i).find(',');
		if (pos != std::string::npos)
		{
			int tmp = 0;
			try {
				tmp = stoi(_lines.at(i).substr(0, pos));
				//cout << tmp << endl;
			}
			catch (invalid_argument ia) {
				setError("Position not a number");
				return false;
			}
			_numbers.push_back(tmp);
			_lines.at(i) = _lines.at(i).substr(pos + 1, _lines.at(i).size());
			//cout << _lines.at(i) << endl;
		}
		else
		{
			lastOperationSuccess = false;
			lastErrorMessage = fs.what();
			return false;
		}
	}
	return true;
}


