#pragma once

#include <vector>
#include "..\World\World.h"
#include <algorithm>

class Strategy
{
protected:
	const string AGGROID = "AGGRO";
	const string DEFFID = "DEFF";
	const string RANDOMID = "RAMDOM";
public:
	virtual string executeSource( vector<class Country*> occupied)=0;
	virtual string executeTarget( Country* sourceCountry)=0;
	virtual string getID() = 0;
};


