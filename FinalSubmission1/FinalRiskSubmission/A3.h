#include <iostream>
#include <string>
#include <vector>
#include "Player\Player.h"
using namespace std;
//Mina Abdel Malek
//Student ID:26951791
//COMP 345 A3 Part Three

//Interface
class AbstractObserver {
public:
	//Abstract Methods
	virtual void update(string name, int numC, int numA, int numCards) = 0;
	virtual void printStats() = 0;
};
//Class Player
/*
class Player1{
public:
	Player1() {}; //Constructor
	~Player1() {}; //Destructor
	string name; //String that will hold the name of the player
	int numCountries; //Number of Countries
	int numArmies; //Number of Armies
	int numCards; //Number of Cards
	vector<class AbstractObserver*> vec; //Array of Observers
	string getName() { return name; } //Accessor
	int getNumCountries() { return numCountries; } //Accessor
	int getNumArmies() { return numArmies; } //Accessor
	int getNumCards() { return numCards; } //Accessor
	void setValue(string n, int numC, int numAr, int numCa) { //Mutator
		name = n; //Adjusts the name to the passed in parameter
		numCountries = numC; //Adjusts the Number of Countries to the passed in parameter
		numArmies = numAr; //Adjusts the Number of Armies to the passed in parameter
		numCards = numCa; //Adjusts the Number of Cards to the passed in parameter
		for (int i = 0; i < vec.size(); i++){
			vec[i]->update(name, numC, numAr, numCa); //Calls the update method
		}

	}
	bool addObserver(AbstractObserver* obs) { //Method that adds an observer to the array
		for (int i = 0; i < vec.size(); i++){
			if (obs == vec[i]) return false; //returns false if it's already there
		}
		vec.push_back(obs); //else prints 
		obs->update(name, numCountries, numArmies, numCards);//updates the new observer added
		return true;

	}
};
*/


//Interface
class IPlayerStats {
protected:
	Player* p;
public:
	virtual void printStats() = 0;
	Player* getPlayer() { return p; }
};
//Concrete
class PlayerStats : public IPlayerStats {
private:
	string name;
public:
	PlayerStats(string basename) { name = basename; }
	void printStats() { cout << name; }
};
//Decorator
class PlayerStatsDecorator : public IPlayerStats {
private:
	IPlayerStats * ips;
public:
	PlayerStatsDecorator(IPlayerStats *n) { ips = n; }
	void printStats() { ips->printStats(); }
};
//Method that inherits from the decorator and prints the number of battles won
class NumOfBattlesWon : public PlayerStatsDecorator {
public:
	int numB;
	NumOfBattlesWon(IPlayerStats *n, int numBattlesWon) : PlayerStatsDecorator(n) {
		numB = numBattlesWon;
	}
	void printStats() {
		PlayerStatsDecorator::printStats();
		cout << "Number of Battles Won: " << numB << endl;
	}
};
//Method that inherits from the decorator and prints the number of reinforcments
class NumOfReinforcments : public PlayerStatsDecorator {
public:
	int numB;
	NumOfReinforcments(IPlayerStats *n, int numReinforcments) : PlayerStatsDecorator(n) {
		numB = numReinforcments;
	}
	void printStats() {
		PlayerStatsDecorator::printStats();
		cout << "Number of Reinforcments: " << numB << endl;
	}
};
//Method that inherits from the decorator and prints the percantage of the world
class PercentageOfWorld : public PlayerStatsDecorator {
public:
	double p;
	PercentageOfWorld(IPlayerStats *n, double percent) : PlayerStatsDecorator(n) {
		p = percent;
	}
	void printStats() {
		PlayerStatsDecorator::printStats();
		cout << "Percentage of World: " << p << endl;
	}
};
//Method that inherits from the decorator and prints the percentage of battles won
class PercentageOfBattlesWon : public PlayerStatsDecorator {
public:
	double p;
	PercentageOfBattlesWon(IPlayerStats *n, double percent) : PlayerStatsDecorator(n) {
		p = percent;
	}
	void printStats() {
		PlayerStatsDecorator::printStats();
		cout << "Percentage of Battles Won: " << p << endl;
	}
};
//This is the connection between the observer and the decorator 
class StatsView : public AbstractObserver, public IPlayerStats {	
public:
	StatsView(Player* pl) {
		p = pl;
	}; //Constructor
	~StatsView() {};//Destrcutor
	void printStats() {
		cout << p->GetPlayerName() << endl;
		cout << "Number of Countries: " << p->getCountries().size() << endl
			<< "Number of Armies: " << p->getNumArmies() << endl
			<< "Number of Cards: " << p->getNumCards() << endl;
	}
	void update(string name, int numCo, int numAr, int numCa) {
		PlayerStats *playerStats = new PlayerStats(name);
		playerStats->printStats();
	}

};
//Test Method 
/*
int main() {
	Player p;
	//p.setValue("Mina ", 5, 10, 15);
	StatsView *v = new StatsView(p);
	v->printStats();
	PercentageOfWorld *s = new PercentageOfWorld(v, 0.5);
	s->printStats();
	PercentageOfBattlesWon *b = new PercentageOfBattlesWon(s, 0.75);
	b->printStats();
	NumOfReinforcments *c = new NumOfReinforcments(b, 200);
	c->printStats();
	NumOfBattlesWon *w = new NumOfBattlesWon(c, 10);
	w->printStats();
	system("pause");

	return 0;
}*/

