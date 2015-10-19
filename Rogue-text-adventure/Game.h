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
	std::random_device dev;
	std::default_random_engine dre{ dev() };

	Map* currentMap = nullptr;
	std::vector<Map*> maps;
	int level = 0;

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
	std::default_random_engine getDRE() { return this->dre; }
	GameState const getGameState();
	RenderState const getRenderState();

	void setGameState(GameState state);
	void setRenderState(RenderState state);
};

