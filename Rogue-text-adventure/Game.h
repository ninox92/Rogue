#pragma once
#include <vector>
#include "GameState.cpp"
#include "RenderState.cpp"
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
	int lxSize = 3;//level X size
	int lySize = 3;//Level Y size
	Hero* hero = nullptr;
	
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

