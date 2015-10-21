using namespace std;
#include "Game.h"
#include <iostream>
#include "ConsoleColor.h"


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
	cout << green << currentMap->show();

	inputController.printMessage(hero->getCurrentRoom()->getRoomDesc()); // Print Room Desc
	inputController.printMessage("Exits: ");
	inputController.printMessage("Enemy NPC: ");
	inputController.printMessage("What would you like to do?");
	inputController.printMessage("[Fight:Flee:Search:Rest:Invertory:Map]"); // Response wanted
	// Action: Flee
	// -- Seprate function with switch
}

void Game::createHero()
{
	string name;
	cout << "Name your awesome hero! ";
	cin >> name;
	hero = new Hero(name);
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
	std::map<std::string, Direction> posDirs = hero->getCurrentRoom()->getAllPossibleMoveDirections();
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
	Map* map = new Map(10, 10, dre);
	map->setLevel(this->level);
	map->create();
	maps.push_back(map);
	currentMap = map;

	//set the hero on the map
	hero->move(currentMap->getStartRoom());
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


