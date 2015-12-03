#ifndef WORLDCONQUEST_H
#define WORLDCONQUEST_H

#include "World.h"

class WorldConquest : public World
{
	bool getNumber(vector<string>&, vector<int>&);
	bool getString(vector<string>&, vector<string>&);
	bool getLinks(string, vector<string>&);

public:
	WorldConquest();
	WorldConquest(string);
	WorldConquest(World*);

	//Operations for the conquest adapter.
	bool toFile();
	bool fromFile();
	

};
#endif