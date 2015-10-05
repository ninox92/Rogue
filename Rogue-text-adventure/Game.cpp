using namespace std;
#include "Game.h"
#include <iostream>

Game::Game()
{
	map = new Map(10, 10);
	this->setGameState(RUNNING);
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


	this->setRenderState(RENDER);
}

void Game::render()
{
	this->setRenderState(WAIT);//Reset the render state to wait
	cout << map->display();
}

void Game::clear()
{
	system("cls");
}

void Game::nextTurn()
{
	
	this->clear();
	//Wait for user input 
	
	//Do a new action
	this->setRenderState(RENDER);//Render for one cycle
}

void Game::getUserInput()
{
	char direction;
	cin >> direction;
	switch (tolower(direction))
	{
	case 'n':
		break;
	case 'e':
		break;
	case 's':
		break;
	case 'w':
		break;
	default:
		break;
	}
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
