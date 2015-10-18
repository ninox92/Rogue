using namespace std;
#include "Game.h"
#include <iostream>


std::random_device dev;
std::default_random_engine dre{ dev() };

Game::Game()
{
	this->createHero();
	this->nextLevel();
	this->setGameState(GameState::RUNNING);
	start();
}


Game::~Game()
{
	delete hero;
}

void Game::start()
{
	
	
	

	cout << "Are you ready for an adventure " + hero->getName() + "?" << endl;
	cout << "You have landed inside a dungeon!" << endl;
	cout << "We must find our way out alive." << endl;
	this->setRenderState(RenderState::RENDER);
}

void Game::render()
{
	this->setRenderState(RenderState::WAIT);//Reset the render state to wait
	cout << currentMap->show();
	nextTurn();
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

void Game::nextTurn()
{
	//this->clear();
	//Wait for user input 
	std::string posDirs = hero->getCurrentRoom()->getAllPossibleMoveDirections();
	Direction d = inputController.getDirectionFromInput(posDirs);
	
	//Do a new action
	this->setRenderState(RenderState::RENDER);//Render for one cycle
}

void Game::createMap()
{
	Map* map = new Map(10, 10, dre);
	map->setLevel(this->level);
	map->create();
	maps.push_back(map);
	currentMap = map;

	//set the hero on the map
	hero->move(currentMap->getStartRoom());
}

void Game::getUserInput()
{
	char direction;
	cin >> direction;
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


