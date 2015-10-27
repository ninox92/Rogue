#pragma once
#include <string>
#include <map>

#include "Actions.cpp"
#include "InputController.h"

class Game;
class Map;
class Hero;

class GameController {
	private:
		Game* game = nullptr;
		Map* cMap = nullptr;
		Hero* cHero = nullptr;
		InputController inputController;
		std::map<std::string, Actions> actionMap = {
			{ "fight", Actions::FIGHT },
			{ "flee", Actions::FLEE },
			{ "search", Actions::SEARCH },
			{ "rest", Actions::REST },
			{ "invertory", Actions::INVERTORY },
			{ "map", Actions::MAP },
			{ "stats", Actions::STATS }
		};
	public:
		GameController(Game* game);
		~GameController();

		void askGameAction();

		void Fight();
		void Flee(bool b);
		void Search();
		void Rest();
		void showInvertory();
		void showMap();
		void showHeroStats();

		std::string getGameActionString();
		std::map<std::string, Actions> getGameActions();
};