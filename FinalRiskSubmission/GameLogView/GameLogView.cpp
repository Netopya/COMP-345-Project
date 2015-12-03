#include "GameLogView.h"

GameLogView::GameLogView(MyObservable* const& observable)
{
	observable->addObserver((MyObserver*)this);

}

void GameLogView::update(MyObservable* observable)
{
	system("cls");

	GameLog* gameLog = (GameLog*)observable;
	
	if (gameLog)
	{
		gameLog->printLastAction();
	}
	
}
