using namespace std;
#include "Game.h"
#include <iostream>

Game::Game()
{
	map = new Map(10, 10);
	this->setGameState(GameState::RUNNING);
	start();
}


Game::~Game()
{
	delete map;
	delete hero;
}

void Game::start()
{
	
	/*string name;
	cout << "Name your awesome hero! ";
	cin >> name;*/
	hero = new Hero("henk");
	cout << "Are you ready for an adventure " + hero->getName() + "?" << endl;
	cout << "You have landed inside a dungeon!" << endl;
	cout << "We must find our way out alive." << endl;

	this->setRenderState(RenderState::RENDER);
}

void Game::render()
{
	this->setRenderState(RenderState::WAIT);//Reset the render state to wait
	cout << map->display();
	//nextTurn();
}

void Game::clear()
{
	system("cls");
}

void Game::nextTurn()
{
	this->clear();
	//Wait for user input 
	Direction d = inputController.getDirectionFromInput();
	
	//Do a new action
	this->setRenderState(RenderState::RENDER);//Render for one cycle
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

GameState Game::getGameState()
{
	return this->gameState;
}

void Game::setRenderState(RenderState state)
{
	this->renderState = state;
}

RenderState Game::getRenderState()
{
	return this->renderState;
}
