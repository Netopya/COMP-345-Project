#pragma once

#include <iostream>;
#include <vector>
#include "..\World\World.h"
#include "Strategy.h"
#include <algorithm>

#include "..\Player\Player.h"
#include "..\World\Country.h"
class Country;
class Player;
class Deff: public Strategy
{
public:
	//Deff():Strategy(){};
	string Deff::executeSource(std::vector<Country*>  occupied);
	
	string Deff::executeTarget(Country* sourceCountry);
};
