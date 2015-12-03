#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include <iostream>
#include "..\MyObservable\MyObservable.h"
#include "..\Player\Player.h"
#include "..\World\Country.h"
#include "..\World\Continent.h"

/*
 * Player observer that displays player information on the console.
 */
class PlayerView : public MyObserver {
public:
	PlayerView(MyObservable* const& observable);
	void update(MyObservable* observable);
};
#endif