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

void GameController::EDijkstra()
{
	this->cMap->revealAllRooms();
	this->cMap->revealEDijkstra();
	showMap();
}

void GameController::BSF()
{
	this->cMap->revealAllRooms();
	this->cMap->revealBFS();
	showMap();
}

void GameController::LVLUP()
{
	game->getHero()->upExp(100);
	showHeroStats();
}

void GameController::HPUP()
{
	Hero* h = game->getHero();
	h->ResetHealth();
	showHeroStats();

}

void GameController::Reveal()
{
	this->cMap->revealAllRooms();
}

void GameController::UseCompass()
{
	//Dijkstra's
	cHero->UseItem("compass", *cMap);
	showMap();
}

void GameController::UseGrenade()
{
	cHero->UseItem("grenade", *cMap);
	showMap();
}

void GameController::UseTalisman()
{
	cout << "De talisman licht op en fluistert dat de trap omhoog " << std::to_string(cMap->talisman()) << " kamers ver weg is" << endl;
	showMap();
}

GameController::GameController(Game* game) : game(game)
{

}

GameController::~GameController()
{
}

void GameController::askWhatToDo()
{
	this->cHero = game->getHero();
	this->cMap = game->getCurrentMap();


	cout << endl;
	string output = inputController.WaitAndGetInput();
	bool nExists = this->actionMap.find(output) != this->actionMap.end();
	bool hExists = this->actionHiddenMap.find(output) != this->actionHiddenMap.end();
	bool sExists = this->actionStatsMap.find(output) != this->actionStatsMap.end();
	bool iExists = this->inventoryMap.find(output) != this->inventoryMap.end();

	// find function by action
	if (nExists)
	{
		Actions normalActions = this->actionMap[output];
		cout << endl;

		switch (normalActions)
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
		}
	}
	if (hExists) {
		Actions hiddenAction = this->actionHiddenMap[output];
		switch (hiddenAction) {
			//Hidden actions
		case Actions::MST:
			MST();
			break;
		case Actions::DIJKSTRA:
			Dijkstra();
			break;
		case Actions::EXTREME_DIJKSTRA:
			EDijkstra();
			break;
		case Actions::BFS:
			BSF();
			break;
		case Actions::LVLUP:
			LVLUP();
			break;
		case Actions::HPUP:
			HPUP();
			break;
		case Actions::REVEAL:
			Reveal();
			break;
		}
	}
	if (sExists) {
		Actions statsAction = this->actionStatsMap[output];
		switch (statsAction)
		{
		case Actions::UP_ATTACK:
			cHero->upAttack();
			cout << "Attack increased by 1, attack now is: " << cHero->getAttack() << endl;
			break;
		case Actions::UP_DEFENSE:
			cHero->upDefense();
			cout << "Defense increased by 1, defense now is: " << cHero->getDefense() << endl;
			break;
		case Actions::UP_MINDFULLNESS:
			cHero->upMindfulness();
			cout << "Mindfullness increased by 1, mindfullness now is: " << cHero->getMindfulness() << endl;
			break;
		}
	}

	if (iExists) {
		Actions iventoryAction = this->inventoryMap[output];
		switch (iventoryAction)
		{
		case Actions::TALISMAN:
			UseTalisman();
			break;
		case Actions::GRENADE:
			UseGrenade();
			break;
		case Actions::COMPASS:
			UseCompass();
			break;
		}

	}

	if (!nExists && !hExists && !sExists && !iExists) askWhatToDo();
}

void GameController::askToUpdateStats()
{
	if (game->getHero()->getRemainingStatPoints() == 0) return;
	cout << "You have " << game->getHero()->getRemainingStatPoints() << " new points left" << endl;
	cout << "To update your hero's stats choose one of these ability's: " << endl;
	for (const auto& i : actionStatsMap) {
		cout << i.first << ";";
	}
	cout << endl;
	askWhatToDo();

	askToUpdateStats();//recursive 
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

	if (cHero->lookForPassage(d)) cHero->move(d);
	else Flee(false);
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
	askWhatToDo();
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
	askToUpdateStats();

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