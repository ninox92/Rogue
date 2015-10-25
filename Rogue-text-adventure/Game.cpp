using namespace std;
#include "Game.h"
#include <list>
#include <iostream>
#include "ConsoleColor.h"
#include "Hero.h"
#include "Map.h"
using std::list;

Game::Game()
{
	this->createHero();
	this->nextLevel();
	this->setGameState(GameState::RUNNING);
	
	this->currentMap->talisman(); 
	start();
	
	
	this->setRenderState(RenderState::RENDER);//Render for one cycle
}


Game::~Game()
{
	delete hero;
}

void Game::start()
{
	cout << "Are you ready for an adventure " + hero->getName() + "?" << endl;
	cout << "We have landed inside a dungeon!" << endl;
	cout << "We must find our way out alive." << endl;
	this->setRenderState(RenderState::RENDER);
}

void Game::render()
{
	this->setRenderState(RenderState::WAIT);//Reset the render state to wait
	currentMap->show();
}

void Game::createHero()
{
	/*string name;
	cout << "Name your awesome hero! ";
	cin >> name;*/
	hero = new Hero("henk");
}

void Game::clear()
{
	system("cls");
}

void Game::nextLevel()
{
	this->level++;
	this->createMap();
}

void Game::askQuestion()
{
	//this->clear();
	map<string, Direction> posDirs = hero->getCurrentRoom()->getAllPossibleMoveDirections();
	Direction d = inputController.getDirectionFromInput(posDirs);
	if (hero->lookForPassage(d)) {
		hero->move(d);
	}
	else {
		askQuestion();
	}
	this->setRenderState(RenderState::RENDER);//Render for one cycle
}

void Game::createMap()
{
	
	Map* map = new Map(lxSize, lySize, this);
	map->setLevel(this->level);
	map->create();
	maps.push_back(map);
	currentMap = map;

	//set the hero on the map
	hero->move(currentMap->getStartRoom());
	level++;
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


