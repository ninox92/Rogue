#pragma once
#include <vector>
#include "GameState.cpp"
#include "RenderState.cpp"
#include "GameController.h"
#include "InputController.h"
#include <random>
#include <stdlib.h>

class Map;
class Hero;

class Game
{
private:
	Map* currentMap = nullptr;
	std::vector<Map*> maps;
	int level = 0;
	int maxLevel = 10;
	int lxSize = 10;//level X size
	int lySize = 10;//Level Y size
	Hero* hero = nullptr;
	GameController gameController;
	InputController inputController;

	GameState gameState = GameState::INIT;
	RenderState renderState = RenderState::WAIT;
	
	void start();
	void clear();
	void nextLevel();
	void createHero();
	void createMap();

public:
	Game();
	~Game();
	
	void render();
	void askQuestion();
	
	Hero* getHero() { return this->hero; }
	GameState const getGameState();
	RenderState const getRenderState();
	int const getMaxLevel() { return this->maxLevel; }

	void setGameState(GameState state);
	void setRenderState(RenderState state);
};

