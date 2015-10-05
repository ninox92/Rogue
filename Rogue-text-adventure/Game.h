#include "Map.h"
#include "Hero.h"
#include "GameState.cpp"
#include "RenderState.cpp"
#include <stdlib.h>
#pragma once


class Game
{
private:
	Map* map;
	Hero* hero;
	GameState gameState = INIT;
	RenderState renderState = WAIT;
	
public:
	Game();
	~Game();
	
	void start();
	void render();
	void clear();
	void nextTurn();

	void getUserInput();

	void setGameState(GameState state);
	GameState getGameState();
	void setRenderState(RenderState state);
	RenderState getRenderState();
};

