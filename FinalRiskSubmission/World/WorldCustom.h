#ifndef WORLDCUSTOM_H
#define WORLDCUSTOM_H

#include "World.h"

class WorldCustom : public World
{

public:
	WorldCustom();
	WorldCustom(string);
	WorldCustom(World*);

	//Operations for the custom adapter.
	bool toFile();
	bool fromFile();

};
#endif