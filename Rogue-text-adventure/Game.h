#pragma once
#include <vector>
#include "GameState.cpp"
#include "RenderState.cpp"
#include "GameController.h"
#include "InputController.h"
#include "FileController.h"

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
	FileController* fileController = new FileController();
	GameController* gameController = nullptr;
	InputController inputController;

	GameState gameState = GameState::INIT;
	RenderState renderState = RenderState::WAIT;
	
	void start();
	void clear();
	
	void createHero();
	void createMap();
	void setLevel(int level);
public:
	Game();
	~Game();
	
	void render();
	
	Hero* getHero() { return this->hero; }
	Map* getCurrentMap() { return this->currentMap; }
	GameState const getGameState();
	RenderState const getRenderState();
	int const getMaxLevel() { return this->maxLevel; }

	void setGameState(GameState state);
	void setRenderState(RenderState state);

	void nextLevel();
	void prevLevel();
	void finish();
};

