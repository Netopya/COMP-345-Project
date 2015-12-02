#pragma once

#include <iostream>;
#include <vector>
#include "..\World\World.h"
#include "Strategy.h"

#include "..\Player\Player.h"
#include "..\World\Country.h"
class Country;
class Player;
class Aggro: public Strategy
{
public:
	Aggro():Strategy(){};
	string Aggro::executeSource(std::vector<Country*>  occupied);
	
	string Aggro::executeTarget(Country* sourceCountry);
};
