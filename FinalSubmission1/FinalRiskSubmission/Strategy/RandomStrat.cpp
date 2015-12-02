#pragma once

#include"RandomStrat.h"

	string RandomStrat::executeSource( std::vector<Country*>  occupied) 
	{
		bool done = false;
		bool exists = false;
		for(int k = 0; k<occupied.size();k++){

			exists = exists ||  occupied[k]->getNumArmies() >= 2;
			if(exists)break;
		}
		if(!exists){
			std::cout << "Attack phase ended"<<std::endl;
			return "0";
		}
		int i;
		while(!done)
		{
			i= (rand() % occupied.size());
			done = occupied[i]->getNumArmies() >= 2;
		}
		return occupied[i]->getName();
		
	}
	string RandomStrat::executeTarget( Country* sourceCountry)
	{
		int target;
		Player* playerID = sourceCountry->getControllingPlayer();
		vector<Country*> adjacentCountries(*(sourceCountry->getConnectedCountries()));
		do{
		target = (rand() % (adjacentCountries.size()));
		}while(playerID == adjacentCountries[target]->getControllingPlayer());
		return adjacentCountries[target]->getName();
	}

