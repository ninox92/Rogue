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
	Map* map;
	Hero* hero;
	InputController inputController;

	GameState gameState = GameState::INIT;
	RenderState renderState = RenderState::WAIT;
	
	
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

