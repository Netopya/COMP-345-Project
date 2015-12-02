#pragma once

#include <vector>
#include "..\World\World.h"
#include <algorithm>

class Strategy
{
public:
	virtual string executeSource( vector<class Country*> occupied)=0;
	virtual string executeTarget( Country* sourceCountry)=0;
};


