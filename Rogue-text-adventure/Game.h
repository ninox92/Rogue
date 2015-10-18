#include "Map.h"
#include "Hero.h"
#include "GameState.cpp"
#include "RenderState.cpp"
#include "InputController.h"
#include <stdlib.h>
#pragma once


class Game
{
private:
	std::vector<Map*> maps;
	int level = 0;
	Map* currentMap = nullptr;
	Hero* hero = nullptr;
	InputController inputController;

	GameState gameState = GameState::INIT;
	RenderState renderState = RenderState::WAIT;
	

	void start();
	void clear();
	void nextLevel();
	void nextTurn();
	void createMap();
	void getUserInput();

public:
	Game();
	~Game();
	
	void render();
	void createHero();
	
	GameState const getGameState();
	RenderState const getRenderState();

	void setGameState(GameState state);
	void setRenderState(RenderState state);
	
};

