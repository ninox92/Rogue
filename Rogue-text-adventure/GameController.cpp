#include "Map.h"
#include "Hero.h"
#include "Game.h"
#include "Room.h"
#include "GameController.h"
#include <iostream>

using namespace std;

void GameController::MST()
{
	this->cMap->revealAllRooms();
	this->cMap->revealMST();
	showMap();
}

void GameController::Dijkstra()
{
	this->cMap->revealAllRooms();
	this->cMap->revealDijkstra();
	showMap();
}

void GameController::BSF()
{
	this->cMap->revealAllRooms();
	this->cMap->revealBFS();
	showMap();
}

GameController::GameController(Game* game) : game(game)
{
	
}

GameController::~GameController()
{
}

void GameController::askGameAction()
{
	this->cHero = game->getHero();
	this->cMap = game->getCurrentMap();
	
	cout << "Action: ";
	string output = inputController.WaitAndGetInput();
	bool exists = this->actionMap.find(output) != this->actionMap.end();
	if (!exists) askGameAction();

	// find function by action
	Actions a = this->actionMap[output];
	cout << endl;

	switch(a)
	{
		case Actions::FIGHT:
			Fight();
			break;
		case Actions::FLEE:
			Flee(true);
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

		//Hidden actions
		case Actions::MST:
			MST();
			break;
		case Actions::DIJKSTRA:
			Dijkstra();
			break;
		case Actions::BFS:
			BSF();
			break;
		case Actions::LVLUP:
			break;
		case Actions::HPUP:

			break;
		case Actions::REVEAL:

			break;
		default:
			break;
	}
}

void GameController::Fight()
{
	// Als er NPC's in de kamer zitten
	// Vechten:
		// Val één van je tegenstanders aan
		// Vlucht in een bepaalde richting weg van je tegenstander(s)
		// Drink een drankje(om bijvoorbeeld te genezen)
		// Gebruik één van je spullen(bijvoorbeeld de heilige handgranaat)
}

void GameController::Flee(bool b)
{
	/* THIS IS TEMPORARY remove this two lines */
	this->cHero = game->getHero();
	this->cMap = game->getCurrentMap();
	if (b) { // Repeat question, dont need to print this below
		map<string, Direction> posDirs = cHero->getCurrentRoom()->getAllPossibleMoveDirections();
		inputController.printDirections(posDirs);
	}

	Direction d = inputController.getDirectionFromInput();
	if (cHero->lookForPassage(d))
		cHero->move(d);
	else 
		Flee(false);
}

void GameController::Search()
{
	// Zoek in de kamer naar een val of spullen
	// Hero: kansberekening aan de hand van mindfulness
}
void GameController::Rest()
{
	// Hero: health = maxHealth
	// Random: kans op nieuwe NPC's in de kamer

}
void GameController::showInvertory()
{
	// Hero: print lijst met spullen
	// Optie: Spullen uit de lijst te gebruiken
	// Of: Niet gebruiken
}

void GameController::showMap()
{
	cMap->show();
	for (const auto& i : legenda) {
		cout << i.first << ": " << i.second << endl;
	}
	

	askGameAction();
}

void GameController::showHeroStats()
{
	cout << "Name:        " << cHero->getName() << endl;
	cout << "Level:       " << cHero->getLevel() << endl;
	cout << "Health:      " << cHero->getHealth() << "/" << cHero->getMaxHealth() << endl;
	cout << "Experience:  " << cHero->getExp() << "/" << cHero->getMaxExp() << endl;
	cout << "Attack:      " << cHero->getAttack() << endl;
	cout << "Defense:     " << cHero->getDefense() << endl;
	cout << "Mindfulness: " << cHero->getMindfulness() << endl << endl;

	askGameAction();
}

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