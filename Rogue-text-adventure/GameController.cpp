#include "Map.h"
#include "Hero.h"
#include "Room.h"
#include "GameController.h"
#include <iostream>

using namespace std;

GameController::GameController()
{
}

GameController::~GameController()
{
}

void GameController::askGameAction(Map* map, Hero* hero)
{
	cMap = map;
	cHero = hero;
	
	cout << "Action: ";
	string output = inputController.WaitAndGetInput();
	bool exists = this->actionMap.find(output) != this->actionMap.end();
	if (!exists) askGameAction(cMap, cHero);

	// find function by action
	Actions a = this->actionMap[output];
	cout << endl;

	switch(a)
	{
		case Actions::FIGHT:
			Fight();
			break;
		case Actions::FLEE:
			Flee();
			break;
		case Actions::SEARCH:
			Search();
			break;
		case Actions::REST:
			Rest();
			break;
		case Actions::INVERTORY:
			showInvertory();
			break;
		case Actions::MAP:
			showMap();
			break;
		case Actions::STATS:
			showHeroStats();
			break;
		default:
			break;
	}
}

void GameController::Fight() {}

void GameController::Flee()
{
	map<string, Direction> posDirs = cHero->getCurrentRoom()->getAllPossibleMoveDirections();
	Direction d = inputController.getDirectionFromInput(posDirs);
	if (cHero->lookForPassage(d)) {
		cHero->move(d);
	}
	else {
		Flee();
	}
}

void GameController::Search() {}
void GameController::Rest() {}
void GameController::showInvertory() {}

void GameController::showMap()
{
	cMap->show();
	askGameAction(cMap, cHero);
}

void GameController::showHeroStats() {}

std::string GameController::getGameActionString()
{
	string s = "[";
	for (auto& kv : this->actionMap) {
		s += kv.first + ":";
	}
	s = s.substr(0, s.size() - 1);
	s += "]";

	return s;
}

std::map<std::string, Actions> GameController::getGameActions()
{
	return this->actionMap;
}