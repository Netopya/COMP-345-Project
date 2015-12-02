#pragma once

#include <vector>
#include "..\World\World.h"
#include <algorithm>

class Strategy
{	
public:
	static const string AGGROID;// = "";
	static const string DEFFID; // = "";
	static const string RANDOMID; // = "";
	static const string NONEID; // = "";

	virtual string executeSource( vector<class Country*> occupied)=0;
	virtual string executeTarget( Country* sourceCountry)=0;
	virtual string getID() = 0;
};


