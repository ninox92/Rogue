#include "Game.h"
#include <list>
#include <iostream>
#include "ConsoleColor.h"
#include "Hero.h"
#include "Map.h"
#include "GameController.h"

using std::list;
using std::cout;
using std::endl;

Game::Game()
{
	this->createHero();
	this->nextLevel();
	this->setGameState(GameState::RUNNING);
	
	
	start();

	this->setRenderState(RenderState::RENDER);//Render for one cycle
}


Game::~Game()
{
	delete hero;
	delete fileController;
}

void Game::start()
{
	this->gameController = new GameController(this);
	clear();
	cout << hero->getName() << ", Are you ready for an adventure!" << endl;
	cout << "You're standing in front of the great Bazinga Dungeon." << endl;
	cout << "This dungeon is full of treasures! But be carefull, you're not alone..." << endl << endl;
	this->setRenderState(RenderState::RENDER);
}

void Game::render()
{
	this->setRenderState(RenderState::WAIT);//Reset the render state to wait
	/*
	//==== Quick testing purposes
	this->currentMap->show();
	cout << "C Level: " << this->level << endl;
	gameController->Flee(true);
	*/

	
	inputController.printMessage(hero->getCurrentRoom()->getRoomDesc());
	inputController.printMessage(hero->getCurrentRoom()->getPassageDesc());
	inputController.printMessage(hero->getCurrentRoom()->getEnemiesDesc());
	inputController.printMessage("What would you like to do?");
	inputController.printMessage(gameController->getGameActionString());
	gameController->askWhatToDo();
	
	clear();

	this->setRenderState(RenderState::RENDER);//Render for one cycle
}

void Game::createHero()
{
	string name;
	cout << "Name your awesome hero! " << endl;
	cout << "Name: ";
	//cin >> name;
	//hero = new Hero(name);
	hero = new Hero("henk", this);
}

void Game::clear()
{
	system("cls");
}

void Game::nextLevel()
{
	if (this->level >= maxLevel) { cout << "FIGHT THE BOSS" << endl;  return; }
	cout << "NEXT LEVEL" << endl;

	if(maps.size() < this->level+1)
		this->createMap();
	else
		setLevel(this->level+1);
}

void Game::prevLevel()
{
	cout << "PREVIOUS LEVEL" << endl;

	if (this->level == 1) return;
	setLevel(this->level-1);
}

void Game::finish()
{
	this->setRenderState(RenderState::RENDER);//Render for one cycle
	this->currentMap->show();

	this->setGameState(GameState::INIT);
	cout << "You'll be marked a legend for ever and more!" << endl;
	cout << "*swimming in gold*" << endl;
	cout << this->hero->getName() << ":'THIS IS AMAZING'" << endl;
	char wait;
	std::cin >> wait;
}

void Game::createMap()
{

	this->level++;
	cout << "Create Level: " << this->level << endl;

	Map* map = new Map(lxSize, lySize, this);
	map->setFileController(fileController);
	map->setLevel(this->level);
	map->create();
	maps.push_back(map);
	currentMap = map;

	//set the hero on the map
	hero->setCurrentRoom(currentMap->getStartRoom());
}

void Game::setLevel(int l)
{
	cout << "Go to level: " << l << ", maps[" << (l-1) << "]" << endl;

	currentMap = maps[l - 1];
	Room* startRoom = l > this->level ? currentMap->getStartRoom() : currentMap->getEndRoom();
	hero->setCurrentRoom(startRoom);
	this->level = l;
}




void Game::setGameState(GameState state)
{
	this->gameState = state;
}

void Game::setRenderState(RenderState state)
{
	this->renderState = state;
}

GameState const Game::getGameState()
{
	return this->gameState;
}

RenderState const Game::getRenderState()
{
	return this->renderState;
}
