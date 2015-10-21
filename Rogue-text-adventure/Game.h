#include "Map.h"
#include "Hero.h"
#include "GameState.cpp"
#include "RenderState.cpp"
#include "GameController.h"
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
	
	GameState const getGameState();
	RenderState const getRenderState();

	void setGameState(GameState state);
	void setRenderState(RenderState state);
	
};

