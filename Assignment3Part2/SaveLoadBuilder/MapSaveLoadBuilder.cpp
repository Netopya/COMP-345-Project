#include "MapSaveLoadBuilder.h"
#include "World\Country.h"

MapSaveLoadBuilder::MapSaveLoadBuilder(World* map)
{
	this->map = map;
}

void MapSaveLoadBuilder::writeElements(ofstream file) {
	vector<Country*> countries = *(map->getCountries());

	file << ID << ' ' << countries.size() << endl;

	for (unsigned i = 0; i < countries.size(); i++)
	{
		file << countries[i]->getName() << ' ' << countries[i]->getControllingPlayer()->GetPlayerName() << ' ' << countries[i]->getNumArmies() << endl;
	}
}