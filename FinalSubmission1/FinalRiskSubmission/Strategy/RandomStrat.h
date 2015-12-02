#pragma once

#include <iostream>;
#include <cstdlib>
#include <ctime>
#include <vector>
#include "..\World\World.h"
#include "Strategy.h"


#include "..\Player\Player.h"
#include "..\World\Country.h"
class Country;
class Player;
class RandomStrat: public Strategy
{
public:
	string executeSource(std::vector<Country*>  occupied);
	
	string executeTarget(Country* sourceCountry);

	string getID() override;
};
